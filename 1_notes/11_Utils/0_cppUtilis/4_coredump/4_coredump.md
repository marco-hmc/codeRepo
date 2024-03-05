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
