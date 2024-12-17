#include <iostream>
#include <sstream>
#include <stack>
#include <string>

class UndoController {
  public:
    void AddOperation(const std::string& operation) {
        stream_ << operation << '\n';
        redoStack_ = std::stack<std::string>();
    }

    void Undo() {
        if (stream_.tellg() > 0) {
            stream_.seekg(-1, std::ios_base::cur);
            std::string operation;
            std::getline(stream_, operation);
            redoStack_.push(operation);
        }
    }

    void Redo() {
        if (!redoStack_.empty()) {
            std::string operation = redoStack_.top();
            redoStack_.pop();
            stream_ << operation << '\n';
        }
    }

    void PrintStream() { std::cout << stream_.str(); }

  private:
    std::stringstream stream_;
    std::stack<std::string> redoStack_;
};

int main() {
    UndoController undoController;

    undoController.AddOperation("操作1");
    undoController.AddOperation("操作2");
    undoController.AddOperation("操作3");

    undoController.PrintStream();

    undoController.Undo();
    undoController.PrintStream();

    undoController.Redo();
    undoController.PrintStream();
    return 0;
}
