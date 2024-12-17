#include <functional>
#include <iostream>

void onButtonClick() { std::cout << "Button clicked!" << '\n'; }

class Button {
  public:
    using ButtonClickHandler = std::function<void()>;

    void registerButtonClickHandler(ButtonClickHandler handler) {
        m_buttonClickHandler = std::move(handler);
    }

    void click() {
        if (m_buttonClickHandler) {
            m_buttonClickHandler();
        }
    }

  private:
    ButtonClickHandler m_buttonClickHandler;
};

int main() {
    Button button;
    button.registerButtonClickHandler(onButtonClick);
    button.click();

    return 0;
}