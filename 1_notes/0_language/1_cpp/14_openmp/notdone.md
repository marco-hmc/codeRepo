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
  一个parallel指令智能被一个default子句修饰。子句default用来控制并行区域内便里昂的共享属性。默认情况，并行区域内便来能耐都是公有的，以下是特殊情况。
  1. 循环指标变量
  2. 区域内的局部变量
  3. 所有在private\firstprivate\lastparivate\deduction子句中列出的变量是私有的。

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