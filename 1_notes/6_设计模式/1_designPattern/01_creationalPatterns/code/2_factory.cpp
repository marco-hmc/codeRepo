#include <iostream>
#include <memory>

// 面试官接口
class Interviewer {
  public:
    virtual ~Interviewer() = default;
    virtual void askQuestions() const = 0;
};

// 开发者类
class Developer : public Interviewer {
  public:
    void askQuestions() const override {
        std::cout << "询问关于设计模式的问题！" << std::endl;
    }
};

// 社区执行者类
class CommunityExecutive : public Interviewer {
  public:
    void askQuestions() const override {
        std::cout << "询问关于社区建设的问题！" << std::endl;
    }
};

// 招聘经理抽象类
class HiringManager {
  public:
    virtual ~HiringManager() = default;

    // 工厂方法
    virtual std::unique_ptr<Interviewer> makeInterviewer() const = 0;

    void takeInterview() const {
        auto interviewer = makeInterviewer();
        interviewer->askQuestions();
    }
};

// 开发经理类
class DevelopmentManager : public HiringManager {
  public:
    std::unique_ptr<Interviewer> makeInterviewer() const override {
        return std::make_unique<Developer>();
    }
};

// 市场经理类
class MarketingManager : public HiringManager {
  public:
    std::unique_ptr<Interviewer> makeInterviewer() const override {
        return std::make_unique<CommunityExecutive>();
    }
};

int main() {
    DevelopmentManager devManager;
    devManager.takeInterview();  // 输出: 询问关于设计模式的问题！

    MarketingManager marketingManager;
    marketingManager.takeInterview();  // 输出: 询问关于社区建设的问题！

    return 0;
}