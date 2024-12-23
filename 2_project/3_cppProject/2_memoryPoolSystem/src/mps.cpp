#include "../include/mps.h"

#include <memory>
#include <stdexcept>

MemPoolList::MemPoolList(void* start, mem_size_t mempool_size)
    : m_mempool_size(mempool_size),
      m_alloc_mem(0),
      m_alloc_prog_mem(0),
      m_alloc_list(nullptr) {
    m_free_list = (MemPoolChunk*)start;
    m_free_list->m_is_free = 1;
    m_free_list->m_alloc_mem = mempool_size;
    m_free_list->m_prev = nullptr;
    m_free_list->m_next = nullptr;
}

////////////////////////////////////////////////////////////////////////

MemPool::MemPool(mem_size_t max_mem, mem_size_t mempool_size)
    : m_last_id(0),
      m_auto_extend(0),
      m_mempool_size(mempool_size),
      m_max_mempool_size(max_mem),
      m_alloc_mempool_size(0),
      m_mlist(nullptr) {
    if (mempool_size > max_mem) {
        throw std::invalid_argument("mempool_size > max_mem");
    }

    std::unique_ptr<char[]> s(new char[sizeof(MemPoolList) + mempool_size]);
    m_mlist = reinterpret_cast<MemPoolList*>(s.get());
    m_mlist->m_start = s.get() + sizeof(MemPoolList);

    m_mlist->m_next = nullptr;
    m_mlist->m_id = m_last_id++;
}

void MemPool::get_memory_list_count(mem_size_t* mlist_len) {}
void MemPool::get_memory_info(mem_size_t* free_list_len,
                              mem_size_t* alloc_list_len) {}
int MemPool::get_memory_id() { return 0; }

// 内存池API
void* MemPool::MemoryPoolAlloc(mem_size_t size) {
    if (size <= 0) return nullptr;
    mem_size_t wantsize = size + sizeof(MemPoolChunk);
    if (wantsize > m_mempool_size) return nullptr;

    return nullptr;
}

void MemPool::MemoryPoolFree(void* ptr) {}
void MemPool::MemoryPoolClear() {}
void MemPool::MemoryPoolDestroy() {}

// 内存池信息API
mem_size_t MemPool::GetTotalMemory() { return 0; }
mem_size_t MemPool::GetAllocMemory() { return 0; }
float MemPool::MemoryPoolGetUsage() { return 0; }
mem_size_t MemPool::GetProgMemory() { return 0; }
float MemPool::MemoryPoolGetProgUsage() { return 0; }
