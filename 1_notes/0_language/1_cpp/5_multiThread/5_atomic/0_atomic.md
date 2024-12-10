## atomic

### 1. atomic的主要成员函数

#### 1.1 操作符
所有操作符都是线程安全的，对于原子变量而言，可以设定内存序进一步提升性能。
而操作符不能带参，自然而言就是默认最高等级的内存序。
相对应的`load()/store()/fetch_add()`其实都是和某个操作符对应的函数实现，就是方便设置内存序用的。

#### 1.2 is_lock_free()
is_lock_free() 方法用于检查原子操作是否是无锁的。无锁操作通常具有更高的性能，因为它们不需要使用互斥锁来同步访问。

不是所有原子类型都是可以无锁的，大部分自定义的原子类型都是有锁的。

#### 1.3 exchange
exchange 是 std::atomic 提供的一个成员函数，用于将原子对象的值设置为新值，并返回旧值。这个操作是原子的，保证了在多线程环境中操作的安全性。

#### 1.4 原子操作api
* store
* load
* fetch_add

#### 1.4 compare_exchange_weak/ compare_exchange_strong
暂时不需要掌握.

### 2. atomic_flag

#### 1. atomic_flag和atomic_bool有什么区别？
atomic_flag一定是无锁的。
atomic_bool是否无锁取决于架构。
一般而言，atomic_flag是用于实现自定义的atomic类型或者无锁编程的。
其他时候用atomic_bool就好了。

#### 2. test_and_set()/clear()怎么用？
test_and_set() 是 std::atomic_flag 和 std::atomic_bool 提供的一个成员函数，用于设置标志为 true，并返回之前的值。这个操作是原子的，通常用于实现简单的锁机制。