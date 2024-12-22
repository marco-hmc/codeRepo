/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <folly/Conv.h>
#include <folly/ProducerConsumerQueue.h>
#include <folly/ThreadLocal.h>
#include <folly/lang/Aligned.h>
#include <folly/logging/xlog.h>
#include <folly/synchronization/Latch.h>
#include <folly/system/ThreadName.h>

#include "cachelib/cachebench/cache/Cache.h"
#include "cachelib/cachebench/util/Exceptions.h"
#include "cachelib/cachebench/util/Parallel.h"
#include "cachelib/cachebench/util/Request.h"
#include "cachelib/cachebench/workload/ReplayGeneratorBase.h"

namespace facebook {
namespace cachelib {
namespace cachebench {

#define BIN_REQ_INT 100000000

struct ReqWrapper {
  ReqWrapper() = default;

  ReqWrapper(const ReqWrapper& other)
      : key_(other.key_),
        sizes_(other.sizes_),
        req_(key_,
             sizes_.begin(),
             sizes_.end(),
             reinterpret_cast<uint64_t>(this),
             other.req_),
        repeats_(other.repeats_) {}

  void updateKey(const std::string& key) {
    key_ = key;
    // Request's key is now std::string_view
    req_.key = key_;
  }

  // current outstanding key
  std::string key_;
  std::vector<size_t> sizes_{1};
  // current outstanding req object
  // Use 'this' as the request ID, so that this object can be
  // identified on completion (i.e., notifyResult call)
  Request req_{key_, sizes_.begin(), sizes_.end(), OpType::kGet,
               reinterpret_cast<uint64_t>(this)};

  // number of times to issue the current req object
  // before fetching a new line from the trace
  uint16_t repeats_{0};
};

// KVReplayGenerator generates the cachelib requests based the trace data
// read from the given trace file(s).
// KVReplayGenerator supports amplifying the key population by appending
// suffixes (i.e., stream ID) to each key read from the trace file.
// In order to minimize the contentions for the request submission queues
// which might need to be dispatched by multiple stressor threads,
// the requests are sharded to each stressor by doing hashing over the key.
class KVReplayGenerator : public ReplayGeneratorBase {
 public:
  // Default order is key,op,size,op_count,key_size,ttl
  enum SampleFields : uint8_t {
    KEY = 0,
    OP,
    SIZE,
    OP_COUNT,
    KEY_SIZE,
    TTL,
    OP_TIME,
    CACHE_HIT,
    END
  };

  const ColumnTable columnTable_ = {
      {SampleFields::OP_TIME, false, {"op_time"}},
      {SampleFields::KEY, true, {"key"}}, /* required */
      {SampleFields::KEY_SIZE, false, {"key_size"}},
      {SampleFields::OP, true, {"op"}}, /* required */
      {SampleFields::OP_COUNT, false, {"op_count"}},
      {SampleFields::SIZE, true, {"size"}}, /* required */
      {SampleFields::CACHE_HIT, false, {"cache_hits"}},
      {SampleFields::TTL, false, {"ttl"}}};

  explicit KVReplayGenerator(const StressorConfig& config)
      : ReplayGeneratorBase(config), traceStream_(config, 0, columnTable_) {
    for (uint32_t i = 0; i < numShards_; ++i) {
      stressorCtxs_.emplace_back(std::make_unique<StressorCtx>(i));
    }
    if (!binaryFileName_.empty()) {
      makeBinaryFile_ = true;
    }
    folly::Latch latch(1);
    if (makeBinaryFile_) {
      std::string filePath;
      if (binaryFileName_[0] == '/') {
        filePath = binaryFileName_;
      } else {
        filePath = folly::sformat("{}/{}", config.configPath, binaryFileName_);
      }
      int fd =
          open(filePath.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
      // first get the number of requests
      auto traceInfo = traceStream_.getTraceRequestStats();
      if (traceInfo.first == 0 && traceInfo.second == 0) {
        close(fd);
        exit(1);
      }
      auto nreqs = traceInfo.first * ampFactor_;
      auto totalKeySize = traceInfo.second * ampFactor_;
      XLOGF(INFO,
            "Started generating binary file from KVReplayGenerator"
            "(amp factor {}, size factor {}, trace requests {})",
            ampFactor_, ampSizeFactor_, traceInfo.first);
      totalReqs_ = nreqs;
      size_t binReqSize = sizeof(BinaryRequest);
      size_t totalSize = sizeof(size_t) + nreqs * binReqSize + totalKeySize + 1;
      size_t totalSizeP =
          totalSize + (PG_SIZE - totalSize % PG_SIZE); // page align
      ftruncate(fd, totalSizeP);
      void* memory =
          mmap(nullptr, totalSizeP, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
      void* copy = memory;
      // the first entry is the total number of requests in the file, so we can
      // calculate the key offset
      size_t* first = reinterpret_cast<size_t*>(memory);
      std::memcpy(first, &nreqs, sizeof(size_t));
      first++;
      memory = reinterpret_cast<void*>(first);
      outputStreamReqs_ = reinterpret_cast<BinaryRequest*>(memory);
      outputStreamKeys_ = reinterpret_cast<char*>(memory);
      outputStreamKeys_ += nreqs * binReqSize;
      folly::setThreadName("cb_binary_gen");
      traceStream_.fastForwardTrace(fastForwardCount_);
      genRequests(latch);
      int res = msync(copy, totalSizeP, MS_SYNC);
      if (res != 0) {
        XLOGF(INFO, "msync error {}", res);
      }
      res = munmap(copy, totalSizeP);
      if (res != 0) {
        XLOGF(INFO, "unmap error {}", res);
      }
      close(fd);
      exit(0);
    } else {
      genWorker_ = std::thread([this, &latch] {
        folly::setThreadName("cb_replay_gen");
        traceStream_.fastForwardTrace(fastForwardCount_);
        genRequests(latch);
      });
    }

    latch.wait();

    XLOGF(INFO,
          "Started KVReplayGenerator (amp factor {}, # of stressor threads {}, "
          "fast forward {})",
          ampFactor_, numShards_, fastForwardCount_);
  }

  virtual ~KVReplayGenerator() {
    XCHECK(shouldShutdown());
    if (genWorker_.joinable()) {
      genWorker_.join();
    }
  }

  // getReq generates the next request from the trace file.
  const Request& getReq(
      uint8_t,
      std::mt19937_64&,
      std::optional<uint64_t> lastRequestId = std::nullopt) override;

  void renderStats(uint64_t, std::ostream& out) const override {
    out << std::endl << "== KVReplayGenerator Stats ==" << std::endl;

    out << folly::sformat("{}: {:.2f} million (parse error: {})",
                          "Total Processed Samples",
                          (double)parseSuccess.load() / 1e6, parseError.load())
        << std::endl;
  }

  void notifyResult(uint64_t requestId, OpResultType result) override;

  void markFinish() override { getStressorCtx().markFinish(); }

  // Parse the request from the trace line and set the ReqWrapper
  bool parseRequest(const std::string& line, std::unique_ptr<ReqWrapper>& req);

  // for unit test
  bool setHeaderRow(const std::string& header) {
    return traceStream_.setHeaderRow(header);
  }

 private:
  // Interval at which the submission queue is polled when it is either
  // full (producer) or empty (consumer).
  // We use polling with the delay since the ProducerConsumerQueue does not
  // support blocking read or writes with a timeout
  static constexpr uint64_t checkIntervalUs_ = 100;
  static constexpr size_t kMaxRequests = 10000;
  static constexpr size_t kMinKeySize = 16;

  using ReqQueue = folly::ProducerConsumerQueue<std::unique_ptr<ReqWrapper>>;

  // StressorCtx keeps track of the state including the submission queues
  // per stressor thread. Since there is only one request generator thread,
  // lock-free ProducerConsumerQueue is used for performance reason.
  // Also, separate queue which is dispatched ahead of any requests in the
  // submission queue is used for keeping track of the requests which need to be
  // resubmitted (i.e., a request having remaining repeat count); there could
  // be more than one requests outstanding for async stressor while only one
  // can be outstanding for sync stressor
  struct StressorCtx {
    explicit StressorCtx(uint32_t id)
        : id_(id), reqQueue_(std::in_place_t{}, kMaxRequests) {}

    bool isFinished() { return finished_.load(std::memory_order_relaxed); }
    void markFinish() { finished_.store(true, std::memory_order_relaxed); }

    uint32_t id_{0};
    std::queue<std::unique_ptr<ReqWrapper>> resubmitQueue_;
    folly::cacheline_aligned<ReqQueue> reqQueue_;
    // Thread that finish its operations mark it here, so we will skip
    // further request on its shard
    std::atomic<bool> finished_{false};
  };

  // Read next trace line from TraceFileStream and fill ReqWrapper
  std::unique_ptr<ReqWrapper> getReqInternal();

  // Used to assign stressorIdx_
  std::atomic<uint32_t> incrementalIdx_{0};

  // A sticky index assigned to each stressor threads that calls into
  // the generator.
  folly::ThreadLocalPtr<uint32_t> stressorIdx_;

  // Vector size is equal to the # of stressor threads;
  // stressorIdx_ is used to index.
  std::vector<std::unique_ptr<StressorCtx>> stressorCtxs_;

  TraceFileStream traceStream_;
  BinaryRequest* outputStreamReqs_;
  char* outputStreamKeys_;
  size_t totalReqs_;
  bool makeBinaryFile_{false};

  std::thread genWorker_;

  // Used to signal end of file as EndOfTrace exception
  std::atomic<bool> eof{false};

  // Stats
  std::atomic<uint64_t> parseError = 0;
  std::atomic<uint64_t> parseSuccess = 0;

  void genRequests(folly::Latch& latch);

  void setEOF() { eof.store(true, std::memory_order_relaxed); }
  bool isEOF() { return eof.load(std::memory_order_relaxed); }

  inline StressorCtx& getStressorCtx(size_t shardId) {
    XCHECK_LT(shardId, numShards_);
    return *stressorCtxs_[shardId];
  }

  inline StressorCtx& getStressorCtx() {
    if (!stressorIdx_.get()) {
      stressorIdx_.reset(new uint32_t(incrementalIdx_++));
    }

    return getStressorCtx(*stressorIdx_);
  }
};

inline bool KVReplayGenerator::parseRequest(const std::string& line,
                                            std::unique_ptr<ReqWrapper>& req) {
  if (!traceStream_.setNextLine(line)) {
    return false;
  }

  auto sizeField = traceStream_.template getField<size_t>(SampleFields::SIZE);
  if (!sizeField.hasValue()) {
    return false;
  }

  // Set key
  auto parsedKey = traceStream_.template getField<>(SampleFields::KEY).value();
  req->updateKey(std::string{parsedKey});

  auto keySizeField =
      traceStream_.template getField<size_t>(SampleFields::KEY_SIZE);
  if (keySizeField.hasValue()) {
    // The key is encoded as <encoded key, key size>.
    // Generate key whose size matches with that of the original one
    size_t keySize = std::max<size_t>(keySizeField.value(), req->key_.size());
    // The key size should not exceed 256
    keySize = std::min<size_t>(keySize, 256);
    auto resizedKey = req->key_;
    resizedKey.resize(keySize, '0');
    req->updateKey(resizedKey);
  }

  // Convert timestamp to seconds.
  auto timestampField =
      traceStream_.template getField<uint64_t>(SampleFields::OP_TIME);
  if (timestampField.hasValue()) {
    uint64_t timestampRaw = timestampField.value();
    uint64_t timestampSeconds = timestampRaw / timestampFactor_;
    req->req_.timestamp = timestampSeconds;
  }

  // Set op
  auto op = traceStream_.template getField<>(SampleFields::OP).value();
  // TODO implement GET_LEASE and SET_LEASE emulations
  if (!op.compare("GET") || !op.compare("GET_LEASE")) {
    req->req_.setOp(OpType::kGet);
  } else if (!op.compare("SET") || !op.compare("SET_LEASE")) {
    req->req_.setOp(OpType::kSet);
  } else if (!op.compare("DELETE")) {
    req->req_.setOp(OpType::kDel);
  } else {
    return false;
  }

  // Set size
  req->sizes_[0] = sizeField.value();

  // Set op_count
  auto opCountField =
      traceStream_.template getField<uint32_t>(SampleFields::OP_COUNT);
  req->repeats_ = static_cast<uint16_t>(opCountField.value_or(1));
  if (!req->repeats_) {
    return false;
  }
  if (config_.ignoreOpCount) {
    req->repeats_ = 1;
  }

  // Set TTL (optional)
  auto ttlField = traceStream_.template getField<size_t>(SampleFields::TTL);
  req->req_.ttlSecs = ttlField.value_or(0);

  return true;
}

inline std::unique_ptr<ReqWrapper> KVReplayGenerator::getReqInternal() {
  auto reqWrapper = std::make_unique<ReqWrapper>();
  do {
    std::string line;
    traceStream_.getline(line); // can throw

    if (!parseRequest(line, reqWrapper)) {
      parseError++;
      XLOG_N_PER_MS(ERR, 10, 1000) << folly::sformat(
          "Parsing error (total {}): {}", parseError.load(), line);
    } else {
      parseSuccess++;
    }
  } while (reqWrapper->repeats_ == 0);

  return reqWrapper;
}

inline void KVReplayGenerator::genRequests(folly::Latch& latch) {
  bool init = true;
  uint64_t nreqs = 0;
  size_t keyOffset = 0;
  size_t lastKeyOffset = 0;
  auto begin = util::getCurrentTimeSec();
  auto binReqStart = util::getCurrentTimeSec();
  while (!shouldShutdown()) {
    std::unique_ptr<ReqWrapper> reqWrapper;
    try {
      reqWrapper = getReqInternal();
    } catch (const EndOfTrace&) {
      if (init) {
        latch.count_down();
      }
      break;
    }

    for (size_t keySuffix = 0; keySuffix < ampFactor_; keySuffix++) {
      std::unique_ptr<ReqWrapper> req;
      // Use a copy of ReqWrapper except for the last one
      if (keySuffix == ampFactor_ - 1) {
        req.swap(reqWrapper);
      } else {
        req = std::make_unique<ReqWrapper>(*reqWrapper);
      }

      size_t keySize = req->key_.size();
      if (ampFactor_ > 1) {
        // Replace the last 4 bytes with thread Id of 4 decimal chars. In doing
        // so, keep at least 10B from the key for uniqueness; 10B is the max
        // number of decimal digits for uint32_t which is used to encode the key
        if (req->key_.size() > kMinKeySize) {
          // trunkcate the key
          size_t newSize = std::max<size_t>(req->key_.size() - 4, kMinKeySize);
          req->key_.resize(newSize, '0');
        }
        req->key_.append(folly::sformat("{:04d}", keySuffix));
      }

      if (makeBinaryFile_) {
        uint8_t op = static_cast<uint8_t>(req->req_.getOp());
        auto valueSize = req->sizes_[0] * ampSizeFactor_;
        // calculate the offset for the key relative to position of current
        // request
        uint64_t relKeyOffset =
            reinterpret_cast<uint64_t>(outputStreamKeys_ + keyOffset) -
            reinterpret_cast<uint64_t>(outputStreamReqs_ + nreqs);
        auto binReq =
            BinaryRequest(static_cast<uint8_t>(keySize), valueSize,
                          req->repeats_, op, req->req_.ttlSecs, relKeyOffset);
        // copy the binary request struct to the output stream (mmap'd file)
        std::memcpy(outputStreamReqs_ + nreqs, &binReq, sizeof(binReq));
        // copy the key to the output stream for keys (same mmap'd file, but at
        // different offset)
        std::memcpy(outputStreamKeys_ + keyOffset, req->key_.c_str(), keySize);
        if ((nreqs % BIN_REQ_INT) == 0 && nreqs > 0) {
          auto end = util::getCurrentTimeSec();
          double reqsPerSec = BIN_REQ_INT / (double)(end - binReqStart);

          uint64_t reqStart = reinterpret_cast<uint64_t>(outputStreamReqs_ +
                                                         (nreqs - BIN_REQ_INT));
          reqStart = reqStart + (PG_SIZE - reqStart % PG_SIZE);
          uint64_t reqEnd =
              reinterpret_cast<uint64_t>(outputStreamReqs_ + nreqs);
          reqEnd = reqEnd + (PG_SIZE - reqEnd % PG_SIZE);
          int rres = madvise(reinterpret_cast<void*>(reqStart),
                             reqEnd - reqStart, MADV_DONTNEED);
          XDCHECK_EQ(rres, 0);

          uint64_t keyStart =
              reinterpret_cast<uint64_t>(outputStreamKeys_ + lastKeyOffset);
          keyStart = keyStart + (PG_SIZE - keyStart % PG_SIZE);
          uint64_t keyEnd =
              reinterpret_cast<uint64_t>(outputStreamKeys_ + keyOffset);
          keyEnd = keyEnd + (PG_SIZE - keyEnd % PG_SIZE);

          int kres = madvise(reinterpret_cast<void*>(keyStart),
                             keyEnd - keyStart, MADV_DONTNEED);
          XDCHECK_EQ(kres, 0);

          XLOGF(INFO, "Parsed: {} reqs ({:.2f} reqs/sec)", nreqs, reqsPerSec);
          lastKeyOffset = keyOffset;
          binReqStart = util::getCurrentTimeSec();
        }
        nreqs++;
        keyOffset += keySize;
      } else {
        auto shardId = getShard(req->req_.key);
        auto& stressorCtx = getStressorCtx(shardId);
        auto& reqQ = *stressorCtx.reqQueue_;

        while (!reqQ.write(std::move(req)) && !stressorCtx.isFinished() &&
               !shouldShutdown()) {
          // ProducerConsumerQueue does not support blocking, so use sleep
          if (init) {
            latch.count_down();
            init = false;
          }
          std::this_thread::sleep_for(
              std::chrono::microseconds{checkIntervalUs_});
        }
        nreqs++;
      }

      if (nreqs >= preLoadReqs_ && init) {
        auto end = util::getCurrentTimeSec();
        double reqsPerSec = nreqs / (double)(end - begin);
        XLOGF(INFO, "Parse rate: {:.2f} reqs/sec", reqsPerSec);
        latch.count_down();
        init = false;
      }
    }
  }

  setEOF();
}

const Request& KVReplayGenerator::getReq(uint8_t,
                                         std::mt19937_64&,
                                         std::optional<uint64_t>) {
  std::unique_ptr<ReqWrapper> reqWrapper;

  auto& stressorCtx = getStressorCtx();
  auto& reqQ = *stressorCtx.reqQueue_;
  auto& resubmitQueue = stressorCtx.resubmitQueue_;

  while (resubmitQueue.empty() && !reqQ.read(reqWrapper)) {
    if (resubmitQueue.empty() && isEOF()) {
      throw cachelib::cachebench::EndOfTrace("Test stopped or EOF reached");
    }
    // ProducerConsumerQueue does not support blocking, so use sleep
    std::this_thread::sleep_for(std::chrono::microseconds{checkIntervalUs_});
  }

  if (!reqWrapper) {
    XCHECK(!resubmitQueue.empty());
    reqWrapper.swap(resubmitQueue.front());
    resubmitQueue.pop();
  }

  ReqWrapper* reqPtr = reqWrapper.release();
  return reqPtr->req_;
}

void KVReplayGenerator::notifyResult(uint64_t requestId, OpResultType) {
  // requestId should point to the ReqWrapper object. The ownership is taken
  // here to do the clean-up properly if not resubmitted
  std::unique_ptr<ReqWrapper> reqWrapper(
      reinterpret_cast<ReqWrapper*>(requestId));
  XCHECK_GT(reqWrapper->repeats_, 0u);
  if (--reqWrapper->repeats_ == 0) {
    return;
  }
  // need to insert into the queue again
  getStressorCtx().resubmitQueue_.emplace(std::move(reqWrapper));
}

} // namespace cachebench
} // namespace cachelib
} // namespace facebook
