/*
 - **隐式实例化**：模板的实例化通常在首次使用时发生，但对于某些成员和操作，编译器需要完整的模板定义。
 - **延迟实例化**：模板成员的定义通常在模板实例化时才会进行。某些特殊情况（如匿名 `union` 和虚函数）会在模板声明时就进行实例化。
 - **两阶段查找**：编译器在模板解析阶段和实例化阶段分别进行查找，以处理受依赖名称和非依赖名称的查找问题。
*/

namespace Implicit_Instance {

    namespace Instance_No_Definition {

        template <typename T>
        struct A;

        A<int>* p = 0;  // OK：只需类模板声明，不需要定义

        template <typename T>
        struct A {
            void f();
        };

        void g(A<int>& a) {  // 只使用类模板声明
            a.f();           // 需要类模板定义，才能调用 A::f()
        }

        template <typename T>
        void A<T>::f() {}

    }  // namespace Instance_No_Definition

    namespace Instance_Override {

        template <typename T>
        struct A {
            A(int);  // 类模板的构造函数
        };

        void f(A<double>) {}
        void f(int) {}

        // 在这个例子中，虽然 `f(42)` 只调用了 `f(int)`，但编译器仍然会实例化 `A<double>`，因为 `f(A<double>)` 作为候选函数之一必须被检查。
        void run() {
            f(42);  // 调用 f(int)，但会实例化 A<double>，即使没被使用
        }

    }  // namespace Instance_Override
}  // namespace Implicit_Instance

namespace Lazy_Instance {
    namespace Instance_Wrong_check {
        /*
        在上面的代码中，模板 `B<int, -1>` 中的 `A<N>` 会在调用时才被实例化。如果 `N <= 0`，就会出现编译错误。
        即使某些成员（如 `error()` 函数）没有被调用，编译器仍然会在实例化时检查 `A<N>` 是否能正确生成。
        如果 `A<N>` 的实例化失败（如 `N` 为负数），编译器会报告错误。

        
        - **虚函数**：虚函数只有在实际调用时才会实例化。如果虚函数没有定义，调用时会导致链接错误。
        - **匿名 `union`**：即使匿名 `union` 中的成员没有被使用，编译器也会实例化它们。

        */

        template <int N>
        struct A {
            int a[N];  // 编译器假设 N 是正整数，如果 N <= 0 将导致错误
        };

        template <typename T, int N>
        struct B {
            void f() {
                A<N> a;  // 如果 N <= 0，调用时会出错
            }

            struct Nested {
                A<N> a;  // N <= 0 时也会出错
            };

            // union 成员会被生成，即使不调用也会导致实例化
            union {
                A<N> a;  // N <= 0 会导致错误
            };
        };

        void run() {
            // Instance_Wrong_check::B<int, -5> a;
            B<int, 5> b{};
            //   b.f();  // 调用时出错
            //   Instance_Wrong_check::B<int, -1>::Nested{};  // 错误
        }
    }  // namespace Instance_Wrong_check

}  // namespace Lazy_Instance

namespace Two_Phase_LookUp {
    /*
    C++ 编译器解析模板时，存在两阶段查找的过程。由于模板参数类型的依赖关系，编译器无法在模板解析阶段完全解析所有名称，尤其是**依赖名称**（dependent name）。因此，编译器会在模板实例化时再次查找这些依赖名称。两阶段查找的过程如下：
    - **第一阶段**：模板解析阶段，编译器会查找所有的**non-dependent name**（非依赖名称）和部分**dependent name**（受依赖名称）。对于某些名称，编译器无法在模板解析时完全解析，必须等到实例化时再进行查找。
   
    - **第二阶段**：模板实例化阶段，称为**实例化点（POI，Point of Instantiation）**。在这一阶段，编译器会查找所有的**dependent name**（受依赖名称），并再次进行**非依赖名称**的查找。

    */

    template <typename T>
    struct A {
        void f() {
            // 在实例化时查找 T::value
            T::value;  // 受依赖名称
        }
    };

    template <typename T>
    struct B {
        void g() {
            A<T> a;
            a.f();  // 调用 f() 时，T::value 会在实例化时查找
        }
    };

    void run() {
        B<int> b;
        b.g();  // 在实例化时查找 T::value
    }
}  // namespace Two_Phase_LookUp

int main() {}