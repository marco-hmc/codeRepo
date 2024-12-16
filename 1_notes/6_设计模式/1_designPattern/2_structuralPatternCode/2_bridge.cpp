
#include <iostream>
#include <string>

// 主题接口
class Theme {
  public:
    virtual ~Theme() = default;
    virtual std::string getColor() const = 0;
};

// 深色主题类
class DarkTheme : public Theme {
  public:
    std::string getColor() const override { return "深黑色"; }
};

// 浅色主题类
class LightTheme : public Theme {
  public:
    std::string getColor() const override { return "浅白色"; }
};

// 水色主题类
class AquaTheme : public Theme {
  public:
    std::string getColor() const override { return "浅蓝色"; }
};

// 页面接口
class WebPage {
  public:
    virtual ~WebPage() = default;
    virtual std::string getContent() const = 0;
};

// 关于页面类
class About : public WebPage {
  public:
    About(Theme* theme) : theme_(theme) {}

    std::string getContent() const override {
        return "关于页面，主题颜色：" + theme_->getColor();
    }

  private:
    Theme* theme_;
};

// 职业页面类
class Careers : public WebPage {
  public:
    Careers(Theme* theme) : theme_(theme) {}

    std::string getContent() const override {
        return "职业页面，主题颜色：" + theme_->getColor();
    }

  private:
    Theme* theme_;
};

int main() {
    // 创建深色主题
    DarkTheme darkTheme;

    // 创建关于页面和职业页面，并应用深色主题
    About about(&darkTheme);
    Careers careers(&darkTheme);

    // 输出页面内容
    std::cout << about.getContent()
              << std::endl;  // 输出: 关于页面，主题颜色：深黑色
    std::cout << careers.getContent()
              << std::endl;  // 输出: 职业页面，主题颜色：深黑色

    return 0;
}
