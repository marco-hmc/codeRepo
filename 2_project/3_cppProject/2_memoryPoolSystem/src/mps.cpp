#include "../include/mps.h"

#include <memory>
#include <stdexcept>

MemoryPoolList::MemoryPoolList(void* start, mem_size_t mempool_size)
    : m_mempool_size(mempool_size),
      m_alloc_mem(0),
      m_alloc_prog_mem(0),
      m_alloc_list(nullptr) {
    m_free_list = (MemPoolChunk*)start;
    m_free_list->is_free = 1;
    m_free_list->alloc_mem = mempool_size;
    m_free_list->prev = nullptr;
    m_free_list->next = nullptr;
}

////////////////////////////////////////////////////////////////////////

MemoryPool::MemoryPool(mem_size_t max_mem, mem_size_t mempool_size)
    : m_last_id(0),
      m_auto_extend(0),
      m_mempool_size(mempool_size),
      m_max_mempool_size(max_mem),
      m_alloc_mempool_size(0),
      m_mlist(nullptr) {
    if (mempool_size > max_mem) {
        throw std::invalid_argument("mempool_size > max_mem");
    }

    m_mlist = new MemoryPoolList(mp);
}

void MemoryPool::get_memory_list_count(mem_size_t* mlist_len) {}
void MemoryPool::get_memory_info(mem_size_t* free_list_len,
                                 mem_size_t* alloc_list_len) {}
int MemoryPool::get_memory_id() { return 0; }

// 内存池API
void* MemoryPool::MemoryPoolAlloc(mem_size_t size) {
    if (size <= 0) return nullptr;
    mem_size_t wantsize = size + sizeof(MemPoolChunk);
    if (wantsize > m_mempool_size) return nullptr;

    return nullptr;
}

void MemoryPool::MemoryPoolFree(void* ptr) {}
void MemoryPool::MemoryPoolClear() {}
void MemoryPool::MemoryPoolDestroy() {}

// 内存池信息API
mem_size_t MemoryPool::GetTotalMemory() { return 0; }
mem_size_t MemoryPool::GetAllocMemory() { return 0; }
float MemoryPool::MemoryPoolGetUsage() { return 0; }
mem_size_t MemoryPool::GetProgMemory() { return 0; }
float MemoryPool::MemoryPoolGetProgUsage() { return 0; }
