## tracy-profiler

### 1. concepts

#### 1.1 tracy-profiler是什么？

#### 1.2 tracyProfiler如何使用？需要配置什么？

1. **下载并编译Tracy**:你可以从Tracy的GitHub页面下载源代码,并使用你的编译器编译它.编译完成后,你会得到一个名为`libtracy.a`的静态库文件.

2. **在你的项目中链接Tracy库**:你需要在你的项目的编译设置中添加Tracy库.具体的步骤取决于你的编译器和构建系统.一般来说,你需要添加Tracy库的路径到你的链接器设置,并添加`-ltracy`到你的链接器标志.

3. **在你的代码中插入Tracy的宏**:你需要在你想要分析的代码段前后添加Tracy的宏.例如,你可以使用`ZoneScoped`宏来标记一个代码块的开始和结束.

```cpp
#include "Tracy.hpp"

void FunctionToProfile()
{
    ZoneScoped;  // 开始一个新的分析区域

    // 这里是你想要分析的代码
    for(int i = 0; i < 1000000; ++i)
    {
        // ...
    }
}
```

4. **运行Tracy Profiler的服务器程序**:Tracy Profiler包含一个名为`tracy.exe`的服务器程序.你需要运行这个程序来收集和查看性能数据.你可以在Tracy的GitHub页面下载这个程序.

5. **运行你的程序**:现在,你可以运行你的程序.Tracy Profiler会自动收集性能数据,并在其用户界面中显示.

以上就是使用Tracy Profiler的基本步骤.需要注意的是,Tracy Profiler的设计目标是实时性能分析,所以它对性能的影响非常小,可以在开发和测试阶段持续使用.


#### 1.3 tracyProfiler的工作原理是什么
Tracy Profiler的工作原理主要基于插桩(Instrumentation)和数据可视化两个方面.

1. **插桩**:Tracy Profiler通过在代码中插入特殊的宏来收集性能数据.这些宏在运行时会记录相关的性能信息,如函数调用的开始和结束时间,线程的状态等.这种方法被称为插桩,它是性能分析的常用技术.

2. **数据收集和传输**:Tracy Profiler在运行时会创建一个单独的线程来收集和发送性能数据.这个线程会定期收集插桩点的数据,并通过网络发送到Tracy Profiler的服务器程序.

3. **数据可视化**:Tracy Profiler的服务器程序会接收并处理收集到的性能数据,并在用户界面中以图形的形式展示.用户可以通过这个界面来查看和分析程序的性能.

这就是Tracy Profiler的基本工作原理.需要注意的是,Tracy Profiler的设计目标是实时性能分析,所以它对性能的影响非常小,可以在开发和测试阶段持续使用.

