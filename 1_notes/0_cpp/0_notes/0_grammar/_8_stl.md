
* 请你回答一下STL里vector的resize和reserve的区别
  * resize()：改变当前容器内含有元素的数量size，eg: vector\<int\>v；v.resize(len)；v的size变为len，**如果原来v的size小于len，那么容器新增（len-size）个元素，元素的值为默认为0**。当v.push_back(3);之后，则是3是放在了v的末尾，即下标为len，此时容器是size为len+1；**如果原来v的size大于len，resize会移除那些超出len的元素同时销毁他们**
  * reserve()：改变当前容器的最大容量（capacity），**它不会生成元素**，只是确定这个容器允许放入多少对象，如果reserve(len)的len值大于当前的capacity，那么会重新分配一块能存len个对象的空间，然后把之前v.size()个对象通过copy construtor复制过来，销毁之前的内存。len值小于当前capacity，不做处理
  * **resize既分配了空间，也创建了对象，可以通过下标访问。resize既修改capacity大小，也修改size大小**
  * **reserve只修改capacity大小，不创建对象，push或insert时才创建，不修改size大小**
* 请你来说一下map和set有什么区别，分别又是怎么实现的？

  * map和set都是C++的关联容器，其底层实现都是红黑树（RB-Tree）。由于 map 和set所开放的各种操作接口，RB-tree 也都提供了，所以几乎所有的 map 和set的操作行为，都只是转调 RB-tree 的操作行为。

  * map和set区别在于：

    * map中的元素是key-value（关键字—值）对：关键字起到索引的作用，值则表示与索引相关联的数据；set与之相对就是关键字的简单集合，set中每个元素只包含一个关键字。
    * **set的迭代器是const的，不允许修改元素的值；map允许修改value，但不允许修改key**。其原因是因为map和set是**根据关键字排序来保证其有序性**的，**如果允许修改key的话，那么首先需要删除该键，然后调节平衡，再插入修改后的键值，调节平衡，如此一来，严重破坏了map和set的结构，导致iterator失效，不知道应该指向改变前的位置，还是指向改变后的位置**。所以STL中将set的迭代器设置成const，不允许修改迭代器的值；而map的迭代器则不允许修改key值，允许修改value值。

    * map支持下标操作，set不支持下标操作。如果find能解决需要，尽可能用find

* functional头文件支持的基于模板的比较函数对象
  * equal_to<Type>、not_equal_to<Type>、greater<Type>、greater_equal<Type>、less<Type>、less_equal<Type>
  * 常用的有greater <Type>()从大到小排序，less <Type>()从小到大排序
