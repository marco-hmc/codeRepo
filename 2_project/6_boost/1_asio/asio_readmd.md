## asio

### 99.quiz 

1. boost里面的coroutine本身是不支持并行执行的，只是作为一种生成器，提供类似于goto的能力，对吗？
是的，Boost.Coroutine 本身并不支持并行执行。它主要作为一种生成器，提供类似于 `goto` 的能力，使得函数可以在多个位置之间切换执行。Boost.Coroutine 允许你在函数中保存和恢复执行状态，但它并不提供并行执行的能力。要实现并行执行，你需要结合其他库，比如 Boost.Asio 或者使用多线程技术。

2. boost的corotuine为什么被弃用了，改用coroutine2了？或者换句话说，在boost中coroutine2和coroutine的区别是什么
Boost.Coroutine 和 Boost.Coroutine2 之间的主要区别在于设计和实现上的改进。Boost.Coroutine2 是对 Boost.Coroutine 的改进版本，解决了一些性能和易用性的问题。以下是两者的主要区别：

1. **性能改进**：Boost.Coroutine2 采用了更高效的实现，减少了上下文切换的开销。
2. **接口改进**：Boost.Coroutine2 提供了更简洁和直观的接口，使得使用更加方便。
3. **更好的兼容性**：Boost.Coroutine2 更好地兼容 C++11 及更高版本的标准，利用了现代 C++ 的特性。
4. **维护性**：Boost.Coroutine2 的代码更易于维护和扩展。

你可以将这些信息添加到你的文档中：

```markdown
2. boost的coroutine为什么被弃用了，改用coroutine2了？或者换句话说，在boost中coroutine2和coroutine的区别是什么
Boost.Coroutine 和 Boost.Coroutine2 之间的主要区别在于设计和实现上的改进。Boost.Coroutine2 是对 Boost.Coroutine 的改进版本，解决了一些性能和易用性的问题。以下是两者的主要区别：

1. **性能改进**：Boost.Coroutine2 采用了更高效的实现，减少了上下文切换的开销。
2. **接口改进**：Boost.Coroutine2 提供了更简洁和直观的接口，使得使用更加方便。
3. **更好的兼容性**：Boost.Coroutine2 更好地兼容 C++11 及更高版本的标准，利用了现代 C++ 的特性。
4. **维护性**：Boost.Coroutine2 的代码更易于维护和扩展。
```