## coredump

### 1. concepts

* **什么是Core Dump？**
    Core Dump文件就是崩溃文件。其命名由来大概如此：早期内存可被称为`core`，而`dump`的意思是倾倒的意思，所以`core dump`可以理解为是进程状态转出到一个文件的意思。而崩溃的时候os会自动做这个事情，得到的文件就是`code dump`文件，只是在中文互联网开发语境，直接就与崩溃关联了。

* **Core Dump 文件记录了什么？**  
    Core Dump 主要记录记录了程序崩溃时的状态：包括内存内容、寄存器状态、内存指针和函数堆栈信息等。  

* **怎么生成？**
    需要在os上设置，windows和linux的设置不一样。windows得到的崩溃文件是.dmp文件，linux得到的文件是core文件。

---

### 2. Core Dump 的原理是什么？

* **核心概念**
    Core Dump 是操作系统在程序崩溃时生成的一个文件，记录了程序崩溃时的内存和寄存器状态。通过分析这个文件，可以了解程序崩溃时的具体情况。

* **具体流程**
    1. **程序崩溃**：当程序由于异常或错误（如访问非法内存、除零错误等）崩溃时，操作系统会捕获这个异常。
    2. **生成 Core Dump 文件**：操作系统将程序的内存内容、寄存器状态、内存指针和函数堆栈信息等保存到一个 `core` 文件中。
    3. **分析 Core Dump 文件**：开发者可以使用调试工具（如 `gdb`）加载 `core` 文件，分析程序崩溃时的状态，找出问题的根源。

* **生成 Core Dump 的条件**
    1. **Shell 资源控制限制**：使用 `ulimit -c` 命令查看 shell 执行程序时的资源限制，如果为 0，则不会生成 Core Dump 文件。可以用 `ulimit -c unlimited` 设置为不限大小。
    2. **读写越界**：如数组访问越界、指针指向错误的内存、字符串读写越界等。
    3. **使用线程不安全的函数**：如读写未加锁保护的共享数据。
    4. **错误使用指针转换**：如将一个类型的指针错误地转换为另一个类型的指针。
    5. **堆栈溢出**：如递归调用过深导致的堆栈溢出。

---

### 3. Core Dump 怎么用？

* **基本设置**
    在大多数 Linux 系统上，可以通过 `ulimit` 命令设置 Core Dump 文件的生成：  
    ```bash
    ulimit -c unlimited  # 设置 Core Dump 文件大小为不限
    ```

* **生成 Core Dump 文件**
    编写一个会导致崩溃的小程序：
    ```c
    #include <stdio.h>

    int main() {
        int *ptr = NULL;
        *ptr = 42;  // 访问空指针，导致崩溃
        return 0;
    }
    ```

    编译并运行程序：
    ```bash
    gcc -g -o coredumpTest coredumpTest.c
    ./coredumpTest
    ```

    如果程序崩溃，会生成一个 `core` 文件。

* **使用 gdb 调试 Core Dump 文件**
    使用 `gdb` 加载可执行文件和 Core Dump 文件进行调试：
    ```bash
    gdb ./coredumpTest core
    ```

    在 gdb 中，可以使用以下命令分析 Core Dump 文件：
    - `bt`：显示崩溃时的堆栈调用信息。
    - `info registers`：显示寄存器状态。
    - `list`：显示崩溃时的代码位置。

---

### 4. 简单例子

编写一个会导致段错误的小程序：
```c
#include <stdio.h>

int main() {
    int *ptr = NULL;
    *ptr = 42;  // 访问空指针，导致段错误
    return 0;
}
```

编译并运行程序：
```bash
gcc -g -o coredumpTest coredumpTest.c
ulimit -c unlimited  # 设置 Core Dump 文件大小为不限
./coredumpTest
```

使用 gdb 调试 Core Dump 文件：
```bash
gdb ./coredumpTest core
```

在 gdb 中分析 Core Dump 文件：
```gdb
(gdb) bt  # 显示崩溃时的堆栈调用信息
(gdb) info registers  # 显示寄存器状态
(gdb) list  # 显示崩溃时的代码位置
```

---

### 总结
- Core Dump 是一种调试工具，用于记录程序崩溃时的状态，帮助开发者分析和修复问题。
- 核心原理是操作系统在程序崩溃时生成一个记录内存和寄存器状态的文件。
- 使用时可以通过 `ulimit` 命令设置 Core Dump 文件的生成，并使用 `gdb` 等调试工具进行分析。
- 通过分析 Core Dump 文件，可以找出程序崩溃的原因，提高程序的稳定性和可靠性。
