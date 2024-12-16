#include <iostream>

// 抽象构建器类
class Builder {
  public:
    // 模板方法
    void build() {
        test();
        lint();
        assemble();
        deploy();
    }

    virtual ~Builder() = default;

  protected:
    virtual void test() = 0;
    virtual void lint() = 0;
    virtual void assemble() = 0;
    virtual void deploy() = 0;
};

// Android构建器类
class AndroidBuilder : public Builder {
  protected:
    void test() override { std::cout << "运行Android测试" << std::endl; }

    void lint() override { std::cout << "静态检查Android代码" << std::endl; }

    void assemble() override { std::cout << "组装Android构建" << std::endl; }

    void deploy() override {
        std::cout << "部署Android构建到服务器" << std::endl;
    }
};

// iOS构建器类
class IosBuilder : public Builder {
  protected:
    void test() override { std::cout << "运行iOS测试" << std::endl; }

    void lint() override { std::cout << "静态检查iOS代码" << std::endl; }

    void assemble() override { std::cout << "组装iOS构建" << std::endl; }

    void deploy() override { std::cout << "部署iOS构建到服务器" << std::endl; }
};

int main() {
    AndroidBuilder androidBuilder;
    androidBuilder.build();

    // 输出:
    // 运行Android测试
    // 静态检查Android代码
    // 组装Android构建
    // 部署Android构建到服务器

    IosBuilder iosBuilder;
    iosBuilder.build();

    // 输出:
    // 运行iOS测试
    // 静态检查iOS代码
    // 组装iOS构建
    // 部署iOS构建到服务器

    return 0;
}
