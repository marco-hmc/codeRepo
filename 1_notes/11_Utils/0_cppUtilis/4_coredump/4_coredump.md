#### (18)coredump是什么 怎么才能coredump
coredump是程序由于异常或者bug在运行时异常退出或者终止,在一定的条件下生成的一个叫做core的文件,这个core文件会记录程序在运行时的内存,寄存器状态,内存指针和函数堆栈信息等等.对这个文件进行分析可以定位到程序异常的时候对应的堆栈调用信息.

coredump产生的条件
1. shell资源控制限制,使用 ulimit -c 命令查看shell执行程序时的资源 ,如果为0,则不会产生coredump.可以用ulimit -c unlimited设置为不限大小.
2. 读写越界,包括:数组访问越界,指针指向错误的内存,字符串读写越界
3. 使用了线程不安全的函数,读写未加锁保护
4. 错误使用指针转换
5. 堆栈溢出


#### (41) 遇到coredump要怎么调试
coredump是程序由于异常或者bug在运行时异常退出或者终止,在一定的条件下生成的一个叫做core的文件,这个core文件会记录程序在运行时的内存,寄存器状态,内存指针和函数堆栈信息等等.对这个文件进行分析可以定位到程序异常的时候对应的堆栈调用信息.

* 使用gdb命令对core文件进行调试

以下例子在Linux上编写一段代码并导致segment fault 并产生core文件
```
mkdir coredumpTest
vim coredumpTest.cpp
```
在编辑器内键入
```
#include<stdio.h>
int main(){
    int i;
    scanf("%d",i);//正确的应该是&i,这里使用i会导致segment fault
    printf("%d\n",i);
    return 0;
}
```
编译
```
g++ coredumpTest.cpp -g -o coredumpTest
```
运行
```
./coredumpTest
```
使用gdb调试coredump
```
gdb [可执行文件名] [core文件名]
```
