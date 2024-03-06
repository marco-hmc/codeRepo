#include <iostream>

// 定义事件处理函数
void onButtonClick() {
    std::cout << "Button clicked!" << std::endl;
}

// 定义事件触发器类
class Button {
public:
    // 定义事件回调函数类型
    typedef void (*ButtonClickHandler)();

    // 注册事件处理函数
    void registerButtonClickHandler(ButtonClickHandler handler) {
        m_buttonClickHandler = handler;
    }

    // 模拟按钮点击事件
    void click() {
        if (m_buttonClickHandler) {
            m_buttonClickHandler();
        }
    }

private:
    ButtonClickHandler m_buttonClickHandler;
};

int main() {
    // 创建按钮对象
    Button button;

    // 注册事件处理函数
    button.registerButtonClickHandler(onButtonClick);

    // 模拟按钮点击事件
    button.click();

    return 0;
}
