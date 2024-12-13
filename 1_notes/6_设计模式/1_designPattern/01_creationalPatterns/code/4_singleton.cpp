#include <iostream>
#include <mutex>

// 饿汉式单例模式
class EagerSingleton {
  public:
    // 禁止拷贝构造和赋值操作
    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;

    // 获取单例实例的静态方法
    static EagerSingleton& GetInstance() {
        static EagerSingleton instance;
        return instance;
    }

    void DoSomething() {
        std::cout << "Doing something in EagerSingleton instance." << std::endl;
    }

  private:
    // 私有构造函数，防止外部实例化
    EagerSingleton() {
        std::cout << "EagerSingleton instance created." << std::endl;
    }
};

// 懒汉式单例模式
class LazySingleton {
  public:
    // 禁止拷贝构造和赋值操作
    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

    // 获取单例实例的静态方法
    static LazySingleton& GetInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = new LazySingleton();
        }
        return *instance;
    }

    void DoSomething() {
        std::cout << "Doing something in LazySingleton instance." << std::endl;
    }

  private:
    // 私有构造函数，防止外部实例化
    LazySingleton() {
        std::cout << "LazySingleton instance created." << std::endl;
    }

    static LazySingleton* instance;
    static std::mutex mutex_;
};

// 初始化静态成员
LazySingleton* LazySingleton::instance = nullptr;
std::mutex LazySingleton::mutex_;

int main() {
    {
        std::cout << "Testing EagerSingleton:\n";
        EagerSingleton& eagerInstance1 = EagerSingleton::GetInstance();
        eagerInstance1.DoSomething();

        EagerSingleton& eagerInstance2 = EagerSingleton::GetInstance();
        eagerInstance2.DoSomething();
    }
    {
        std::cout << "\nTesting LazySingleton:\n";
        LazySingleton& lazyInstance1 = LazySingleton::GetInstance();
        lazyInstance1.DoSomething();

        LazySingleton& lazyInstance2 = LazySingleton::GetInstance();
        lazyInstance2.DoSomething();
    }
    return 0;
}