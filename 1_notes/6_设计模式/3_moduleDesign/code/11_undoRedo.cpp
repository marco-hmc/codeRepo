#include <iostream>
#include <stack>

class Model {
  private:
    int data;

  public:
    explicit Model(int initialData) : data(initialData) {}
    void setData(int newData) { data = newData; }
    int getData() const { return data; }
};

class UndoRedoManager {
  private:
    std::stack<Model> undoStack;
    std::stack<Model> redoStack;

  public:
    void performUndo() {
        if (!undoStack.empty()) {
            Model currentModel = undoStack.top();
            undoStack.pop();
            redoStack.push(currentModel);
            std::cout << "Undo: Data restored to " << currentModel.getData()
                      << '\n';
        } else {
            std::cout << "Undo: No more operations to undo" << '\n';
        }
    }

    void performRedo() {
        if (!redoStack.empty()) {
            Model currentModel = redoStack.top();
            redoStack.pop();
            undoStack.push(currentModel);
            std::cout << "Redo: Data restored to " << currentModel.getData()
                      << '\n';
        } else {
            std::cout << "Redo: No more operations to redo" << '\n';
        }
    }

    void performOperation(Model& model, int newData) {
        undoStack.push(model);
        model.setData(newData);
        redoStack = std::stack<Model>();
        std::cout << "Performed operation: Data set to " << newData << '\n';
    }
};

int main() {
    Model model(0);
    UndoRedoManager undoRedoManager;

    undoRedoManager.performOperation(model, 10);
    undoRedoManager.performOperation(model, 20);
    undoRedoManager.performOperation(model, 30);

    undoRedoManager.performUndo();
    undoRedoManager.performUndo();

    undoRedoManager.performRedo();
    return 0;
}