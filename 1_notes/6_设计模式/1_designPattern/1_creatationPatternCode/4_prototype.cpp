#include <iostream>
#include <memory>
#include <string>

class Sheep {
  public:
    Sheep(const std::string& name,
          const std::string& category = "Mountain Sheep")
        : name_(name), category_(category) {}

    void setName(const std::string& name) { name_ = name; }

    std::string getName() const { return name_; }

    void setCategory(const std::string& category) { category_ = category; }

    std::string getCategory() const { return category_; }

    std::unique_ptr<Sheep> clone() const {
        return std::make_unique<Sheep>(*this);
    }

  private:
    std::string name_;
    std::string category_;
};

int main() {
    auto original = std::make_unique<Sheep>("Jolly");
    std::cout << original->getName() << std::endl;      // 输出: Jolly
    std::cout << original->getCategory() << std::endl;  // 输出: Mountain Sheep

    // 克隆并修改所需内容
    auto cloned = original->clone();
    cloned->setName("Dolly");
    std::cout << cloned->getName() << std::endl;      // 输出: Dolly
    std::cout << cloned->getCategory() << std::endl;  // 输出: Mountain Sheep

    return 0;
}
