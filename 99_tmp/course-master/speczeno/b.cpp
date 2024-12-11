#include <iostream>
#include <memory>
#include <string>

struct IObject {
    IObject() = default;
    IObject(IObject const &) = default;
    IObject &operator=(IObject const &) = default;
    virtual ~IObject() = default;

    virtual void eatFood() = 0;
    virtual std::shared_ptr<IObject> clone() const = 0;
};

struct CatObject : IObject {
    std::string m_catFood = "someFish";

    void eatFood() override {
        std::cout << "eating " << m_catFood << std::endl;
        m_catFood = "fishBones";
    }

    [[nodiscard]] std::shared_ptr<IObject> clone() const override {
        return std::make_shared<CatObject>(*this);
    }
};

struct DogObject : IObject {
    std::string m_dogFood = "someMeat";

    void eatFood() override {
        std::cout << "eating " << m_dogFood << std::endl;
        m_dogFood = "meatBones";
    }

    std::shared_ptr<IObject> clone() const override {
        return std::make_shared<DogObject>(*this);
    }
};

void eatTwice(IObject *obj) {
    std::shared_ptr<IObject> newObj = obj->clone();
    obj->eatFood();
    newObj->eatFood();
}

int main() {
    std::shared_ptr<CatObject> cat = std::make_shared<CatObject>();
    std::shared_ptr<DogObject> dog = std::make_shared<DogObject>();

    eatTwice(cat.get());
    eatTwice(dog.get());

    return 0;
}
