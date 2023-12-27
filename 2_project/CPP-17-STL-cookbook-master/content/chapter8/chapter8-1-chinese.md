# 转换不同的时间单位——std::ratio

C++11之后，STL具有了很多用来测量和显示时间的新类型和函数。STL这部分内容放在`std::chrono`命名空间中。

## How to do it...

   ```c++
   #include <iostream>
   #include <chrono>
   #include <ratio>
   #include <cmath>
   #include <iomanip>
   #include <optional>
   
   using namespace std; 
   ```

2. `chrono::duration`经常用来表示所用时间的长度，其为秒的倍数或小数，所有STL的程序都由整型类型进行特化。
   ```c++
   using seconds = chrono::duration<double>;
   ```

   ```c++
   using milliseconds = chrono::duration<
   	double, ratio_multiply<seconds::period, milli>>;
   ```
   ```c++
   using microseconds = chrono::duration<
   	double, ratio_multiply<seconds::period, micro>>;
   ```

5. 现在我们实现一个函数，会用来从用户的输入中读取一个字符串，并且统计用户输入所用的时间。这个函数没有参数，在返回用户输入的同时，返回所用的时间，我们用一个组对(pair)将这两个数进行返回：

   ```c++
   static pair<string, seconds> get_input()
   {
   	string s;
     	const auto tic (chrono::steady_clock::now());
      if (!(cin >> s)) {
       	return { {}, {} };
      }
      const auto toc (chrono::steady_clock::now());   
   	return {s, toc - tic};
   } 
   ```

9. 现在让我们来实现主函数，使用一个循环获取用户的输入，直到用户输入正确的字符串为止。在每次循环中，我们都会让用户输入"C++17"，然后调用`get_input`函数：

   ```c++
   int main()
   {
       while (true) {
       	cout << "Please type the word \"C++17\" as"
       			" fast as you can.\n> ";
           
       	const auto [user_input, diff] = get_input();
   		if (user_input == "") { break; }
         if (user_input == "C++17") {
            cout << "Bravo. You did it in:\n"
               << fixed << setprecision(2)
               << setw(12) << diff.count()
               << " seconds.\n"
               << setw(12) << milliseconds(diff).count()
               << " milliseconds.\n"
               << setw(12) << microseconds(diff).count()
               << " microseconds.\n";
            break;
         } else {
               cout << "Sorry, your input does not match."
                     " You may try again.\n";
         }
      }
    }
    ```

13. 编译并运行程序，就会得到如下的输出。第一次输入时，会有一个错误，程序会让我们重新进行输入。在正确输入之后，我们就会得到输入所花费的时间：

    ```c++
    $ ./ratio_conversion
    Please type the word "C++17" as fast as you can.
    > c+17
    Sorry, your input does not match. You may try again.
    Please type the word "C++17" as fast as you can.
    > C++17
    Bravo. You did it in: 
            2.82 seconds.
         2817.95 milliseconds.
      2817948.40 microseconds.
    ```

## How it works...

本节中对不同时间单位进行转换是，我们需要先选择三个可用的时钟对象的一个。其分别为`system_clock`，`steady_clock`和`high_resolution_clock`，这三个时钟对象都在`std::chrono`命名空间中。他们有什么区别呢？让我们来看一下：

| 时钟类型                                                     | 特性                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [system_clock](https://zh.cppreference.com/w/cpp/chrono/system_clock) | 表示系统级别的实时挂钟。想要获取本地时间的话，这是个正确的选择。 |
| [steady_clock](https://zh.cppreference.com/w/cpp/chrono/steady_clock) | 表示单调型的时间。这个时间是不可能倒退的，而时间倒退可能会在其他时钟上发生，比如：其最小精度不同，或是在冬令时和夏令时交替时。 |
| [high_resolution_clock](https://zh.cppreference.com/w/cpp/chrono/high_resolution_clock) | STL中可统计最细粒度时钟周期的时钟。                          |

OK，现在来对合适的时间对象进行选择，可以通过`chrono::steady_clock::now()`对时间点进行保存。`now`函数会返回一个`chrono::time_point<chrono::steady_clock>`类的值。两个点之间的差就是所用时间间隔，或`chrono::duration`类型的时间长度。这个类型是本节的核心类型，其看起来有点复杂。让我们来看一下`duration`模板类的签名：

```c++
template<
    class Rep,
    class Period = std::ratio<1>
> class duration;
```

我们需要改变的参数类为`Rep`和`Period`。`Rep`很容易解释：其只是一个数值类型用来保存时间点的值。对于已经存在的STL时间单位，都为`long long int`型。本节中，我们选择了`double`。因为我们的选择，保存的时间描述也可以转换为毫秒或微秒。当`chrono::seconds`类型记录的时间为1.2345秒时，其会舍入成一个整数秒数。这样，我们就能使用`chrono::microseconds`来保存`tic`和`toc`之间的时间，并且将其转化为粒度更加大的时间。正因为选择`double`作为`Rep`传入，可以对计时的精度在丢失较少精度的情况下，进行向上或向下的调整。

对于我们的计时单位，我们采取了`Rep = double`方式，所以会在`Period`上有不同的选择：

```c++
using seconds = chrono::duration<double>;
using milliseconds = chrono::duration<double,
	ratio_multiply<seconds::period, milli>>;
using microseconds = chrono::duration<double,
	ratio_multiply<seconds::period, micro>>;
```

`seconds`是最简单的时间单位，其为`Period = ratio<1>`，其他的时间单位就只能进行转换。1毫秒是千分之一秒，所以我们将使用`milli`特化的`seconds::period`转化为秒时，就要使用`std::ratio<1, 1000>`类型(`std::ratio<a, b>`表示分数值a/b)。`ratio_multiply`类型是一个编译时函数，其表示对应类型的结果是多个`ratio`值累加。

可能这看起来非常复杂，那就让我们来看一个例子吧：`ratio_multiply<ratio<2, 3>, ratio<4, 5>>`的结果为`ratio<8, 15>`，因为`(2/3) * (4/5) = 8/15`。

我们结果类型定义等价情况如下：

```c++
using seconds = chrono::duration<double, ratio<1, 1>>;
using milliseconds = chrono::duration<double, ratio<1, 1000>>;
using microseconds = chrono::duration<double, ratio<1, 1000000>>;
```

上面列出的类型，很容易的就能进行转换。当我们具有一个时间间隔`d`，其类型为`seconds`，我们就能将其转换成`milliseconds`。转换只需要通过构造函数就能完成——`milliseconds(d)`。

