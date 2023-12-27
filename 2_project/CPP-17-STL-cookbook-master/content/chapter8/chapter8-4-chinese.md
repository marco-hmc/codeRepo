# 对元组使用函数

## How to do it...

我们将实现一个程序，其能对元组值进行打包和解包。然后，我们将看到在不了解元组中元素的情况下，如何使用元组：

1. 包含必要的头文件，并声明所使用的命名空间：

   ```c++
   #include <iostream>
   #include <iomanip>
   #include <tuple>
   #include <functional>
   #include <string>
   #include <list>
   
   using namespace std;
   static void print_student(size_t id, const string &name, double gpa)
   {
       cout << "Student " << quoted(name)
           << ", ID: " << id
           << ", GPA: " << gpa << '\n';
   }
   int main()
   {
       using student = tuple<size_t, string, double>;
       student john {123, "John Doe"s, 3.7};
   	{
           const auto &[id, name, gpa] = john;
           print_student(id, name, gpa);
       }
       cout << "-----\n";
       auto arguments_for_later = {
           make_tuple(234, "John Doe"s, 3.7),
           make_tuple(345, "Billy Foo"s, 4.0),
           make_tuple(456, "Cathy Bar"s, 3.5),
       };
       for (const auto &[id, name, gpa] : arguments_for_later) {
      		print_student(id, name, gpa);
       }
       cout << "-----\n";
   	apply(print_student, john);
   	cout << "-----\n";
       for (const auto &args : arguments_for_later) {
       	apply(print_student, args);
       }
       cout << "-----\n";
   }
   ```

9. 编译并运行程序，我们就能得到如下的输出：

   ```c++
   $ ./apply_functions_on_tuples
   Student "John Doe", ID: 123, GPA: 3.7
   -----
   Student "John Doe", ID: 234, GPA: 3.7
   Student "Billy Foo", ID: 345, GPA: 4
   Student "Cathy Bar", ID: 456, GPA: 3.5
   -----
   Student "John Doe", ID: 123, GPA: 3.7
   -----
   Student "John Doe", ID: 234, GPA: 3.7
   Student "Billy Foo", ID: 345, GPA: 4
   Student "Cathy Bar", ID: 456, GPA: 3.5
   -----
   ```

