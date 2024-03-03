#include <iostream>
#include <stack>
#include <string>
#include <sstream>

class UndoController {
public:
    void AddOperation(const std::string& operation) {
        // 将操作添加到流中
        stream_ << operation << std::endl;
        // 清空重做栈
        redoStack_ = std::stack<std::string>();
    }

    void Undo() {
        if (stream_.tellg() > 0) {
            // 将流指针移动到上一个操作的位置
            stream_.seekg(-1, std::ios_base::cur);
            // 读取上一个操作
            std::string operation;
            std::getline(stream_, operation);
            // 将操作添加到重做栈中
            redoStack_.push(operation);
        }
    }

    void Redo() {
        if (!redoStack_.empty()) {
            // 从重做栈中取出最近一次撤销的操作
            std::string operation = redoStack_.top();
            redoStack_.pop();
            // 将操作添加到流中
            stream_ << operation << std::endl;
        }
    }

    void PrintStream() {
        // 将流中的操作打印出来
        std::cout << stream_.str();
    }

private:
    std::stringstream stream_;
    std::stack<std::string> redoStack_;
};

int main() {
    UndoController undoController;

    undoController.AddOperation("操作1");
    undoController.AddOperation("操作2");
    undoController.AddOperation("操作3");

    undoController.PrintStream(); // 打印流中的操作

    undoController.Undo(); // 撤销最后一次操作
    undoController.PrintStream(); // 打印流中的操作

    undoController.Redo(); // 重做最后一次撤销的操作
    undoController.PrintStream(); // 打印流中的操作

    return 0;
}
