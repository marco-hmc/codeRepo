#include <iostream>
#include <memory>
#include <vector>

class Monkey;
class Lion;
class Dolphin;

class AnimalVisitor {
  public:
    virtual ~AnimalVisitor() = default;
    virtual void visitMonkey(const Monkey &monkey) = 0;
    virtual void visitLion(const Lion &lion) = 0;
    virtual void visitDolphin(const Dolphin &dolphin) = 0;
};

class Animal {
  public:
    virtual ~Animal() = default;
    virtual void accept(AnimalVisitor &visitor) const = 0;
};

class Monkey : public Animal {
  public:
    void accept(AnimalVisitor &visitor) const override {
        visitor.visitMonkey(*this);
    }
    std::string shout() const { return "Ooh oo aa aa!"; }
};

class Lion : public Animal {
  public:
    void accept(AnimalVisitor &visitor) const override {
        visitor.visitLion(*this);
    }
    std::string roar() const { return "Roaaar!"; }
};

class Dolphin : public Animal {
  public:
    void accept(AnimalVisitor &visitor) const override {
        visitor.visitDolphin(*this);
    }
    std::string speak() const { return "Tuut tutt tuutt!"; }
};

class FeedingVisitor : public AnimalVisitor {
  public:
    void visitMonkey(const Monkey &monkey) override {
        std::cout << "喂猴子: " << monkey.shout() << std::endl;
    }
    void visitLion(const Lion &lion) override {
        std::cout << "喂狮子: " << lion.roar() << std::endl;
    }
    void visitDolphin(const Dolphin &dolphin) override {
        std::cout << "喂海豚: " << dolphin.speak() << std::endl;
    }
};

class PerformanceVisitor : public AnimalVisitor {
  public:
    void visitMonkey(const Monkey &monkey) override {
        std::cout << "猴子表演: " << monkey.shout() << std::endl;
    }
    void visitLion(const Lion &lion) override {
        std::cout << "狮子表演: " << lion.roar() << std::endl;
    }
    void visitDolphin(const Dolphin &dolphin) override {
        std::cout << "海豚表演: " << dolphin.speak() << std::endl;
    }
};

int main() {
    std::vector<std::shared_ptr<Animal>> animals = {
        std::make_shared<Monkey>(), std::make_shared<Lion>(),
        std::make_shared<Dolphin>()};

    FeedingVisitor feedingVisitor;
    PerformanceVisitor performanceVisitor;

    std::cout << "喂食时间:" << std::endl;
    for (const auto &animal : animals) {
        animal->accept(feedingVisitor);
    }

    std::cout << "\n表演时间:" << std::endl;
    for (const auto &animal : animals) {
        animal->accept(performanceVisitor);
    }

    return 0;
}
