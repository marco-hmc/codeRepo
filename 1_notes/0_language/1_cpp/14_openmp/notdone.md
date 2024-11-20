* 并行控制：parallel
    静态模式
    动态模式
    嵌套模式
    条件模式
    并行构造
    * 并行区域
    * 工作共享
      * 同构
        * 规则循环
          * for,single,task, simd
        * 不规则循环和递归
          * task
        * 非循环
          * sections
      * 异构
        * target
* 工作共享：
    for, sections, single
    task, simd, target
* 数据环境：
    共享变量: shared, copyprivate(copyin)
    私有变量: private， firstprivate, lastprivate
    default
    threadPrivate
    reduction

* 线程同步：
    barrier, master, critical
    atomic, flush, ordered
* 环境变量：
    omp_schedule, stackSize
    omp_dynamic, omp_nested
    omp_num_threads
* 库函数：
    * 运行环境操作函数：
    * 锁函数：
    * 时间函数：