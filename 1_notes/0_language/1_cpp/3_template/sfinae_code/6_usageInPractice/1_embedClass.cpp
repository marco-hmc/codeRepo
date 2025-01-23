/*
    嵌入类通常指的是在类的内部定义其他类，这些嵌入类通常是与外部类紧密相关的辅助类。
    嵌入类的主要作用是帮助实现某些特定的功能，如实现容器中的迭代器、数据结构的节点、策略类等。
*/

#include <iostream>

namespace embed_class_demo {
    template <typename T>
    class MyContainer {
      public:
        MyContainer() : data(new T[10]), size(10) {}

        class Iterator {
          public:
            Iterator(T* ptr) : ptr(ptr) {}

            T& operator*() { return *ptr; }
            Iterator& operator++() {
                ++ptr;
                return *this;
            }
            bool operator!=(const Iterator& other) const {
                return ptr != other.ptr;
            }

          private:
            T* ptr;
        };

        Iterator begin() { return Iterator(data); }
        Iterator end() { return Iterator(data + size); }

      private:
        T* data;
        size_t size;
    };

    void task() {
        MyContainer<int> container;
        for (auto it = container.begin(); it != container.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}  // namespace embed_class_demo

int main() {
    embed_class_demo::task();
    return 0;
}