// lazy
// 懒汉式单例模式在第一次调用 getInstance
// 方法时才会创建实例.在懒汉式中,实例是在静态方法内部创建的,通常使用静态局部变量,保证只有在第一次调用时才会创建实例.
// 特点:
// 延迟实例化,只有在第一次使用时才创建实例.
// 在多线程环境下,需要考虑线程安全性,以确保只创建一个实例.
class Singleton {
private:
 Singleton() = default;
 ~Singleton(){};
 Singleton(const Singleton &) = delete;
 Singleton &operator=(const Singleton &);

public:
  static Singleton &getInstance() {
    static Singleton instance;
    return instance;
  }
};

///////////////////////////////////////////
// hungry
// 饿汉式单例模式在类加载时就创建实例,无论是否需要使用.这通常通过在类内部直接实例化一个静态成员变量来实现.
// 特点:
// 线程安全,因为实例是在类加载时就创建的.
// 不延迟实例化,无论是否使用,实例都会被创建.
class Singleton2 {
private:
  static Singleton2 instance;

private:
  Singleton2();
  ~Singleton2();
  Singleton2(const Singleton2 &);
  Singleton2 &operator=(const Singleton2 &);

public:
  static Singleton2 &getInstance() { return instance; }
};

Singleton2 Singleton2::instance;

// 如果程序一开始就需要使用单例对象,而且希望线程安全,可以选择饿汉式.
// 如果程序启动时不一定需要使用单例对象,而且希望延迟实例化,可以选择懒汉式.在懒汉式中,需要注意线程安全性,可以通过加锁等机制来保证

int main() {}