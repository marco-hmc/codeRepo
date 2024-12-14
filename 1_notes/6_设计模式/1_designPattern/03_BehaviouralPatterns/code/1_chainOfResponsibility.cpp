#include <iostream>
#include <memory>
#include <stdexcept>

// 抽象账户类
class Account {
  protected:
    std::shared_ptr<Account> successor;
    float balance;

  public:
    void setNext(std::shared_ptr<Account> account) { successor = account; }

    void pay(float amountToPay) {
        if (canPay(amountToPay)) {
            std::cout << "使用 " << getAccountType() << " 支付了 "
                      << amountToPay << " 美元" << std::endl;
        } else if (successor) {
            std::cout << "无法使用 " << getAccountType() << " 支付。继续..."
                      << std::endl;
            successor->pay(amountToPay);
        } else {
            throw std::runtime_error("没有账户有足够的余额");
        }
    }

    bool canPay(float amount) const { return balance >= amount; }

    virtual std::string getAccountType() const = 0;
};

// 银行账户类
class Bank : public Account {
  public:
    Bank(float balance) { this->balance = balance; }

    std::string getAccountType() const override { return "银行账户"; }
};

// PayPal账户类
class Paypal : public Account {
  public:
    Paypal(float balance) { this->balance = balance; }

    std::string getAccountType() const override { return "PayPal账户"; }
};

// 比特币账户类
class Bitcoin : public Account {
  public:
    Bitcoin(float balance) { this->balance = balance; }

    std::string getAccountType() const override { return "比特币账户"; }
};

int main() {
    // 准备链条
    //      bank -> paypal -> bitcoin
    //
    // 优先级：银行
    //      如果银行不能支付，则使用PayPal
    //      如果PayPal不能支付，则使用比特币

    auto bank = std::make_shared<Bank>(100);        // 银行账户，余额100
    auto paypal = std::make_shared<Paypal>(200);    // PayPal账户，余额200
    auto bitcoin = std::make_shared<Bitcoin>(300);  // 比特币账户，余额300

    bank->setNext(paypal);
    paypal->setNext(bitcoin);

    // 尝试使用优先级最高的银行账户支付
    bank->pay(259);

    // 输出结果
    // ==============
    // 无法使用银行账户支付。继续...
    // 无法使用PayPal账户支付。继续...
    // 使用比特币账户支付了259美元！

    return 0;
}
