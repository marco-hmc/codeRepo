#pragma once

#define mem_size_t unsigned long long
#define KB (mem_size_t)(1 << 10)
#define MB (mem_size_t)(1 << 20)
#define GB (mem_size_t)(1 << 30)

class MemoryPool;

class MemoryPoolList {
  public:
    struct MemPoolChunk {
        mem_size_t alloc_mem;
        struct MemPoolChunk *prev, *next;
        int is_free;
    };

  public:
    MemoryPoolList(void *start, mem_size_t mempool_size);

  public:
    char *m_start;
    unsigned int m_id;
    mem_size_t m_mempool_size;  // 固定值 每个内存池最大内存
    mem_size_t m_alloc_mem;  // 统计值 当前池内已分配的内存总大小
    mem_size_t
        m_alloc_prog_mem;  // 统计值 当前池内实际分配给应用程序的内存总大小(减去内存管理元信息)
    MemPoolChunk *m_free_list, *m_alloc_list;
    struct MemPoolList *m_next;
};

class MemoryPool {
  public:
    MemoryPool(mem_size_t max_mem, mem_size_t mempool_size);
    ~MemoryPool() = default;

    MemoryPool(const MemoryPool &) = default;
    MemoryPool &operator=(const MemoryPool &) = default;

    void get_memory_list_count(mem_size_t *mlist_len);
    void get_memory_info(mem_size_t *free_list_len, mem_size_t *alloc_list_len);
    int get_memory_id();

    void *MemoryPoolAlloc(mem_size_t size);
    void MemoryPoolFree(void *ptr);
    void MemoryPoolClear();
    void MemoryPoolDestroy();

    mem_size_t GetTotalMemory();
    mem_size_t GetAllocMemory();
    float MemoryPoolGetUsage();
    mem_size_t GetProgMemory();
    float MemoryPoolGetProgUsage();

    unsigned int m_last_id;
    int m_auto_extend;
    mem_size_t m_mempool_size;      // 固定值 每个内存池最大内存
    mem_size_t m_max_mempool_size;  // 固定值 所有内存池加和总上限
    mem_size_t m_alloc_mempool_size;  // 统计值 当前已分配的内存池总大小
    struct MemPoolList *m_mlist;
};