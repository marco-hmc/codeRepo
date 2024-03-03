#### poll和epoll的区别
epoll是poll的升级版.其实poll和epoll都是用于同时监视多个文件描述符的.poll需要自己管理一组文件描述符的集合,而epoll就使得内核为我们管理这个结构体的数组,通过epoll_create.epoll不是一个函数,他是一组函数的实现.<br>
* poll布置完监视任务就需要取得监视的结果,而epoll就是用epoll_wait函数进行阻塞监视并返回监视结果.
epoll更成熟.<br>
* nginx和apache对比

* 同步/异步/阻塞/非阻塞的理解
* * 同步互斥