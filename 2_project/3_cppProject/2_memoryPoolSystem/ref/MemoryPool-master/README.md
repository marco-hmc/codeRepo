# MemoryPool

一个极简内存池实现(基于 First Fit 算法, 可扩展)

要一口气预分配大内存来管理

## Log

- 18-1-7 12.53 增加了自动扩展 (内存池耗尽时自动新扩展一个 mempoolsize 大小的内存)
- 18-5-27 1.10 改进输出信息 增强测试程序(详见 main.cpp)
- 19-3-18 11.05 改进格式, 修复潜在 bug
- 19-4-1 20:46 增加线程安全选项, 修改了自动扩展逻辑.
- 19-10-14 21:44 reformat 修改多线程启用模式(详见下面 Tips), 移除 Calloc
- 24-01-16 修复一个初始化失败导致的内存泄漏 #11, 新增部分注释, 调整部分变量命名

## Next

- 伙伴内存管理
- 读写锁

## Makefile

- run_single_test 运行单线程测试
- run_multi_test 运行多线程测试
- run_example 运行 example.c

## Example

```c
#include "memorypool.h"
#include <stdio.h>

struct TAT
{
    int T_T;
};

mem_size_t max_mem = 2*GB + 1000*MB + 1000*KB;
mem_size_t mempool_size = 1*GB + 500*MB + 500*KB;

int main()
{
    MemoryPool *mp = MemoryPoolInit(max_mem, mempool_size);
    struct TAT *tat = (struct TAT *)MemoryPoolAlloc(mp, sizeof(struct TAT));
    tat->T_T = 2333;
    printf("%d\n", tat->T_T);
    MemoryPoolFree(mp, tat);
    MemoryPoolClear(mp);
    MemoryPoolDestroy(mp);
    return 0;
}
```

## API

- 预定义宏

`KB` `MB` `GB`

- 内存池

`mem_size_t` => `unsigned long long`

`MemoryPoolInit` 参数(`mem_size_t maxmempoolsize`, `mem_size_t mempoolsize`)

> `maxmempoolsize`: 内存池字节数上限
>
> `mempoolsize`: 内存池字节数 (maxmempoolsize 与 mempoolsize 不相等时会自动扩展, 直到上限)

`MemoryPoolAlloc` 行为与系统 malloc 一致(参数多了一个)

`MemoryPoolFree` 行为与系统 free 一致(返回值 0 为正常)

```c
MemoryPool* MemoryPoolInit   (mem_size_t maxmempoolsize, mem_size_t mempoolsize);
void*       MemoryPoolAlloc  (MemoryPool *mp, mem_size_t wantsize);
int         MemoryPoolFree   (MemoryPool *mp, void *p);
MemoryPool* MemoryPoolClear  (MemoryPool *mp);
int         MemoryPoolDestroy(MemoryPool *mp);
```

- 获取内存池信息

`MemoryPoolGetUsage` 获取当前内存池已使用内存比例

`MemoryPoolGetProgUsage` 获取内存池中真实分配内存比例(除去了内存池管理结构占用的内存)

```c
// 总空间
mem_size_t GetTotalMemory(MemoryPool* mp);
// 实际分配空间
mem_size_t GetUsedMemory     (MemoryPool *mp);
float      MemoryPoolGetUsage(MemoryPool *mp);
// 数据占用空间
mem_size_t GetProgMemory     (MemoryPool *mp);
float      MemoryPoolGetProgUsage(MemoryPool *mp);
```

## Tips

- 可通过注释`test.c`里的`#include "memorypool.h"`来切换对比系统`malloc` `free`和内存池
- 线程安全(需通过提供编译选项`-D _Z_MEMORYPOOL_THREAD_`或者`memorypool.h`文件增加`#define _Z_MEMORYPOOL_THREAD_`)
- 多食用`MemoryPoolClear` (多线程情况下慎用)
- 在 **2GB** 数据量 **顺序分配释放** 的情况下比系统`malloc` `free`平均快 **30%-50%** (食用`MemoryPoolClear`效果更明显)
- `mem_size_t`使用`unsigned long long`以支持 4GB 以上内存管理
- 大量小块内存分配会有 **20%-30%** 内存空间损失(用于存储管理结构体)

new 是属于内核调用，
用户态切换到内核态，是有开销的。只有内核态才能进行内存的开辟。
所以一般内存池的核心思想在于，提前开辟，开辟一个大的内存空间 arr。
如果之后要使用就用上面的元素。
这样子只有一次内核态的系统调用函数去 malloc。

否则，每次开辟内存，都要跑到内核态调用系统 api,开销会一些。
