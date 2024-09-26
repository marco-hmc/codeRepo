#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class FIFOQueue {
   private:
    int start{};
    int end{};
    bool flag{};

    int initCap;
    std::vector<int> vec;
    std::condition_variable cv;
    std::mutex m;

   public:
    explicit FIFOQueue(int capacity) : initCap(capacity), vec(capacity) {}

    bool enqueue(int v) {
        std::unique_lock<std::mutex> lk(m);
        while (flag) {
            cv.wait(lk);
        }
        end = (end + 1) % initCap;
        vec[end] = v;
        cv.notify_all();
        return true;
    }

    int dequeue() {
        std::unique_lock<std::mutex> lk(m);
        if (start != end) {
            int val = vec[start];
            start = (start + 1) % initCap;
            flag = false;
            cv.notify_all();
            return val;
        }

        flag = false;
        cv.notify_all();
        return -1;
    }
};

void testFIFOQueue() {
    FIFOQueue queue(5);

    std::thread producer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            queue.enqueue(i);
            std::cout << "Enqueued: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::thread consumer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            int value = queue.dequeue();
            std::cout << "Dequeued: " << value << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    });

    producer.join();
    consumer.join();
}

int main() {
    testFIFOQueue();
    return 0;
}

/*
1. 这个实现有问题的，找出实现有问题的地方
*/