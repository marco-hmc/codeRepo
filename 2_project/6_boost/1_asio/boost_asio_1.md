# asio

## synchronous
### execution context
- boost::asio::io_context object
- boost::asio::thread_pool object
- boost::asio::system_context. 

* Your program will have at least one I/O execution context, such as an 
* This I/O execution context represents your program's link to the operating system's I/O services.

### I/O object

- boost::asio::ip::tcp::socket socket(io_context); // / TCP socket

When a synchronous connect operation is performed, the following sequence of events occurs:

### steps
1. Your program initiates the connect operation by calling the I/O object:

```c++
socket.connect(server_endpoint);
```
2. The I/O object forwards the request to the I/O execution context.

3. The I/O execution context calls on the operating system to perform the connect operation.

4. The operating system returns the result of the operation to the I/O execution context.

5. The I/O execution context translates any error resulting from the operation into an object of type boost::system::error_code. An error_code may be compared with specific values, or tested as a boolean (where a false result means that no error occurred). The result is then forwarded back up to the I/O object.

6. The I/O object throws an exception of type boost::system::system_error if the operation failed. 
```c++
boost::system::error_code ec;
socket.connect(server_endpoint, ec);
```
then the error_code variable ec would be set to the result of the operation, and no exception would be thrown.

## asynchronous
这段文字解释了使用 Boost.Asio 库进行异步连接操作的基本流程。以下是逐步的中文解释：

1. **程序发起连接操作**：
   - 你的程序通过调用 I/O 对象来发起连接操作：
     ```c++
     socket.async_connect(server_endpoint, your_completion_handler);
     ```
   - 其中 [`your_completion_handler`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A44%2C%22character%22%3A38%7D%7D%5D%5D "Go to definition") 是一个函数或函数对象，其签名如下：
     ```c++
     void your_completion_handler(const boost::system::error_code& ec);
     ```
   - 具体的签名取决于正在执行的异步操作，参考文档会指明每个操作的适当形式。

2. **I/O 对象转发请求**：
   - I/O 对象将连接请求转发给 I/O 执行上下文（execution context）。

3. **I/O 执行上下文通知操作系统**：
   - I/O 执行上下文通知操作系统开始一个异步连接操作。

4. **操作系统完成连接操作**：
   - 操作系统完成连接操作后，将结果放入一个队列中，等待 I/O 执行上下文来处理。

5. **程序调用 [`io_context::run()`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A59%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition")**：
   - 当使用 [`io_context`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A59%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition") 作为 I/O 执行上下文时，你的程序必须调用 [`io_context::run()`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A59%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition")（或类似的 [`io_context`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A59%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition") 成员函数）来检索结果。
   - 调用 [`io_context::run()`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A59%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition") 会阻塞，直到所有异步操作完成。因此，通常在启动第一个异步操作后立即调用它。

6. **处理结果**：
   - 在 [`io_context::run()`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A59%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition") 的调用过程中，I/O 执行上下文会从队列中取出操作结果，将其转换为 [`error_code`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A45%2C%22character%22%3A54%7D%7D%5D%5D "Go to definition")，然后传递给你的完成处理程序（completion handler）。

### 总结

这段文字简化了 Boost.Asio 的操作流程，具体步骤如下：

1. 程序调用 [`async_connect`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A44%2C%22character%22%3A7%7D%7D%5D%5D "Go to definition") 发起异步连接。
2. I/O 对象将请求转发给 I/O 执行上下文。
3. I/O 执行上下文通知操作系统开始异步连接。
4. 操作系统完成连接后，将结果放入队列。
5. 程序调用 [`io_context::run()`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2F0_codeRepo%2F2_project%2F6_boost%2F1_asio%2Fboost_asio_1.md%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A59%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition") 来处理结果。
6. I/O 执行上下文取出结果并调用完成处理程序。

通过这种方式，Boost.Asio 实现了异步 I/O 操作，使得程序可以在等待 I/O 操作完成时继续执行其他任务，从而提高并发性和效率。