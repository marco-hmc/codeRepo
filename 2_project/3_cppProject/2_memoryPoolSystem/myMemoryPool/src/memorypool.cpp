#include "../include/memorypool.h"

MemoryPool::MemoryPool(mem_size_t max_mem, mem_size_t mempool_size) {}
// MemoryPool::~MemoryPool() {}

void MemoryPool::get_memory_list_count(mem_size_t* mlist_len) {}
void MemoryPool::get_memory_info(mem_size_t* free_list_len,
                                 mem_size_t* alloc_list_len) {}
int MemoryPool::get_memory_id() {}

void* MemoryPool::MemoryPoolAlloc(mem_size_t size) {}
void MemoryPool::MemoryPoolFree(void* ptr) {}
void MemoryPool::MemoryPoolClear() {}
void MemoryPool::MemoryPoolDestroy() {}

mem_size_t MemoryPool::GetTotalMemory() {}
mem_size_t MemoryPool::GetAllocMemory() {}
float MemoryPool::MemoryPoolGetUsage() {}
mem_size_t MemoryPool::GetProgMemory() {}
float MemoryPool::MemoryPoolGetProgUsage() {}
