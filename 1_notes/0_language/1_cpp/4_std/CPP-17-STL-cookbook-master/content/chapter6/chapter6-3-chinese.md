# 使用STL数值算法实现傅里叶变换

信号处理领域傅里叶变换是非常重要和著名的公式。这个公式发现于200年前，其计算机用例实很多了。傅里叶变换可以用于音频/图像/视频压缩、音频滤波、医疗图像设备和用于辨识声音的手机引用。

因为其应用领域广泛，STL也试图将其用在数值计算领域。傅里叶变换只是其中一个例子，同样也是非常棘手的一个。其公式如下所示：

![](../../images/chapter6/6-3-1.png)

公式基于累加和的变换。累加中的每个元素是输入信号向量中的一个数据点和表达式`exp(-2 * i * ...)`的乘积。这里需要一些工程数学的知识，你需要简单的了解复数的概念，如果你没有相关的知识，了解概念就可以了。仔细观察这个公式，其就是将信号中的所有数据点进行加和(信号数据的长度为N)，其循环索引值为j。其中k是另一个循环变量，因为傅里叶变换计算出的是一组值。在这组值中，每一个数据点都表示着一段重复波形的幅值和相位，这些信息不包含在原始数据中。当使用循环对其进行实现时，代码可能就会写成下面这样：

```c++
csignal fourier_transform(const csignal &s) {
    csignal t(s.size());
    const double pol {-2.0 * M_PI / s.size()};
    for (size_t k {0}; k < s.size(); ++k) {
        for (size_t j {0}; j < s.size(); ++j) {
            t[k] += s[j] * polar(1.0, pol * k * j);
        }
    }
    return t;
}
```

这里`csignal`的类型可能是`std::vector`，其每个元素都是一个复数。对于复数而言，STL中已经有了对应的数据结构可以对其进行表示——`std::complex`。`std::polar`函数计算得是`exp(-2 * i * ...)`部分。

这样实现看起来也挺好，不过本节中我们将使用STL工具对其进行实现。

## How to do it...

本节，我们将实现傅里叶变换和逆变换，然后会对一些信号进行转换：

1. 首先，包含必要的头文件和声明所使用的命名空间：

   ```c++
   #include <iostream>
   #include <complex>
   #include <vector>
   #include <algorithm>
   #include <iterator>
   #include <numeric>
   #include <valarray>
   #include <cmath>
   
   using namespace std;

   using cmplx = complex<double>;
   using csignal = vector<cmplx>;

   class num_iterator {
   	size_t i;
   public:
   	explicit num_iterator(size_t position) : i{position} {}
       
   	size_t operator*() const { return i; }
       
   	num_iterator& operator++() {
   		++i;
   		return *this;
   	}
       
   	bool operator!=(const num_iterator &other) const {
   		return i != other.i;
   	}

   csignal fourier_transform(const csignal &s, bool back = false)
   {
   	csignal t (s.size());

   	const double pol {2.0 * M_PI * (back ? -1.0 : 1.0)};
   	const double div {back ? 1.0 : double(s.size())};

       auto sum_up ([=, &s] (size_t j) {
           return [=, &s] (cmplx c, size_t k) {
           	return c + s[k] *
           		polar(1.0, pol * k * j / double(s.size()));
           };
       });

   	auto to_ft ([=, &s](size_t j){
           return accumulate(num_iterator{0},
                             num_iterator{s.size()},
                             cmplx{},
                             sum_up(j))
           / div;
       });

       transform(num_iterator{0}, num_iterator{s.size()},
       		 begin(t), to_ft);
       return t;
   }

   static auto gen_cosine (size_t period_len){
       return [period_len, n{0}] () mutable {
       	return cos(double(n++) * 2.0 * M_PI / period_len);
       };
   }

    static auto gen_square_wave (size_t period_len)
    {
        return [period_len, n{period_len*7/4}] () mutable {
        	return ((n++ * 2 / period_len) % 2) * 2 - 1.0;
        };
    }

    template <typename F>
    static csignal signal_from_generator(size_t len, F gen)
    {
        csignal r (len);
        generate(begin(r), end(r), gen);
        return r;
    }

    static void print_signal (const csignal &s)
    {
        auto real_val ([](cmplx c) { return c.real(); });
        transform(begin(s), end(s),
        		 ostream_iterator<double>{cout, " "}, real_val);
        cout << '\n';
    }

    int main()
    {
    	const size_t sig_len {100};

        auto cosine (signal_from_generator(sig_len,
            gen_cosine( sig_len / 2)));
    
        auto square_wave (signal_from_generator(sig_len,
            gen_square_wave(sig_len / 2)));

        auto trans_sqw (fourier_transform(square_wave));
    
        fill (next(begin(trans_sqw), 10), prev(end(trans_sqw), 10), 0);
        auto mid (fourier_transform(trans_sqw, true));

        print_signal(cosine);
        print_signal(fourier_transform(cosine));
        
        print_signal(mid);
        print_signal(trans_sqw);
        
        print_signal(square_wave);
        print_signal(fourier_transform(square_wave));
    }
    ```

17. 编译并运行程序，终端上会打印出大量的数据。如果这里使用绘图输出，就可以看到如下的结果：

    ![](../../images/chapter6/6-3-2.png)

## How it works...

这段代码又两个比较难理解的部分。第一个是傅里叶变换本身，另一个是使用可变Lambda表达式生成信号数据。

首先，我们来看一下傅里叶变换。其核心部分在循环中实现(虽然没有在我们实现中这样做，但可以结合代码看下介绍中的公式)，可能会以如下方式实现：

```c++
for (size_t k {0}; k < s.size(); ++k) {
    for (size_t j {0}; j < s.size(); ++j) {
    	t[k] += s[j] * polar(1.0, pol * k * j / double(s.size()));
    }
}
```

基于STL算法`std::transform`和`std::accumulate`，我们完成了自己的例子，总结一下就类似如下的伪代码：

```
transform(num_iterator{0}, num_iterator{s.size()}, ...
	accumulate((num_iterator0}, num_iterator{s.size()}, ...
		c + s[k] * polar(1.0, pol * k * j / double(s.size()));
```

和循环相比，结果完全一样。当然，使用STL算法也可以产生不太好的代码。不管怎么样吧，这个实现是不依赖所选用的数据结构。其对于列表也起作用(虽然这没有太大的意义)。另一个好处是，在C++17中STL很容易并行(将在本书的另一个章节进行介绍)，当需要并行的时候，我们就需要对纯循环进行重构和拆分，将其放入指定的线程中(除非使用类似OpenMP这样的并发库，其会自动的将循环进行重构)。

下一个难点是信号生成。让我来看一下另一个`gen_cosine`:

```c++
static auto gen_cosine (size_t period_len)
{
    return [period_len, n{0}] () mutable {
    	return cos(double(n++) * 2.0 * M_PI / period_len);
    };
}
```

每一个Lambda表达式代表一个函数对象，其会在每次调用时改变自身的状态。其状态包含两个变量`period_len`和`n`。变量n会在每次调用时，进行变更。在不同的时间点上，得到的是不同的信号值，并且在时间增加时会使用`n++`对`n`的值进行更新。为了获得信号值的数组，我们创建了辅助函数`signal_from_generator`：

```c++
template <typename F>
static auto signal_from_generator(size_t len, F gen)
{
    csignal r (len);
    generate(begin(r), end(r), gen);
    return r;
}
```

这个函数会通过所选长度创建一个信号`vector`，并且调用`std::generate`对数据点进行填充。数组r中的每一个元素，都会调用一个`gen`函数。`gen`函数是是一种自修改函数对象，我们使用相同的方式创建了`gen_cosine`对象。

> Note：
>
> 本节例子中，STL没有让代码更加的优雅。如果将范围库添加入STL(希望在C++20时加入)，那么可能就会有改观。