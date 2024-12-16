#include <iostream>
#include <memory>
#include <unordered_map>

// 任何将被缓存的东西都是享元。
// 这里的茶类型将是享元。
class KarakTea {
  public:
    void serveTea() const { std::cout << "提供卡拉克茶" << std::endl; }
};

// 充当工厂并保存茶
class TeaMaker {
  public:
    std::shared_ptr<KarakTea> make(const std::string& preference) {
        if (availableTea_.find(preference) == availableTea_.end()) {
            availableTea_[preference] = std::make_shared<KarakTea>();
        }
        return availableTea_[preference];
    }

  private:
    std::unordered_map<std::string, std::shared_ptr<KarakTea>> availableTea_;
};

// 茶馆类
class TeaShop {
  public:
    TeaShop(std::shared_ptr<TeaMaker> teaMaker) : teaMaker_(teaMaker) {}

    void takeOrder(const std::string& teaType, int table) {
        orders_[table] = teaMaker_->make(teaType);
    }

    void serve() const {
        for (const auto& order : orders_) {
            std::cout << "为桌子 " << order.first << " 提供茶: ";
            order.second->serveTea();
        }
    }

  private:
    std::unordered_map<int, std::shared_ptr<KarakTea>> orders_;
    std::shared_ptr<TeaMaker> teaMaker_;
};

int main() {
    std::shared_ptr<TeaMaker> teaMaker = std::make_shared<TeaMaker>();
    TeaShop shop(teaMaker);

    shop.takeOrder("卡拉克茶", 1);
    shop.takeOrder("卡拉克茶", 2);
    shop.takeOrder("卡拉克茶", 3);

    shop.serve();  // 输出: 为桌子 1 提供茶: 提供卡拉克茶
                   //      为桌子 2 提供茶: 提供卡拉克茶
                   //      为桌子 3 提供茶: 提供卡拉克茶

    return 0;
}
