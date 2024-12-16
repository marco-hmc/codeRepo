#include <iostream>
#include <memory>
#include <string>

// 备忘录类
class Memento {
  public:
    Memento(const std::string& state) : state_(state) {}

    std::string getState() const { return state_; }

  private:
    std::string state_;
};

// 原发器类
class TextEditor {
  public:
    void setText(const std::string& text) { text_ = text; }

    std::string getText() const { return text_; }

    std::shared_ptr<Memento> save() const {
        return std::make_shared<Memento>(text_);
    }

    void restore(const std::shared_ptr<Memento>& memento) {
        text_ = memento->getState();
    }

  private:
    std::string text_;
};

int main() {
    TextEditor editor;
    editor.setText("Hello, World!");
    std::cout << "当前文本: " << editor.getText()
              << std::endl;  // 输出: 当前文本: Hello, World!

    // 保存当前状态
    auto savedState = editor.save();

    // 修改文本
    editor.setText("Hello, Design Patterns!");
    std::cout << "修改后的文本: " << editor.getText()
              << std::endl;  // 输出: 修改后的文本: Hello, Design Patterns!

    // 恢复之前的状态
    editor.restore(savedState);
    std::cout << "恢复后的文本: " << editor.getText()
              << std::endl;  // 输出: 恢复后的文本: Hello, World!

    return 0;
}