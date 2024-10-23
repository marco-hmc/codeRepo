to readingRepo
the lazy fox jumps over brown dog

## 怎么开始阅读一个大项目？

### 
1. 知道意图，看文档，问人
2. 断点调试
3. 修改
4. 重构（减少重复代码，函数提取）
5. 添加测试



#### CPU、内存占用过高问题定位

* https://blog.csdn.net/GR9527/article/details/108456151
* http://www.cxyzjd.com/article/qq_32273965/106749858
* 步骤：
  * 使用`top`定位到占用CPU高的进程PID   然后按`shift+p`按照CPU排序
  * 再用`ps -mp pid -o THREAD,tid,time`查询进程中,那个线程的cpu占用率高记住TID

* 如何读取一个10G文件，cat一个10g文件会发生什么

  - 强行 cat 一个大文件会造成内存溢出，通常将**cat**命令和**split**命令混合使用。
  - 比如内存是250M， 那么将10G的文件切分成若干个250M的文件，然后文本查找
