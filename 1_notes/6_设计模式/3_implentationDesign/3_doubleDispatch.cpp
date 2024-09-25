#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

/*
### 什么是 Double Dispatch

Double Dispatch 是一种设计模式，允许在运行时根据两个对象的实际类型来选择调用适当的函数。它解决了基于多个对象的多态行为问题，常用于处理对象之间的交互，例如碰撞检测。

### 如何解决 Double Dispatch

1. **使用 RTTI（运行时类型识别）**：
   - 通过 `typeid` 和 `dynamic_cast` 来识别对象的实际类型，并调用相应的处理函数。

2. **使用虚函数**：
   - 在基类中定义多个重载的虚函数，派生类实现这些虚函数，根据对象的实际类型调用相应的处理函数。

3. **模拟虚函数表**：
   - 在派生类中定义多个处理函数，并在基类中调用这些函数，模拟虚函数表的行为。

4. **初始化模拟虚函数表**：
   - 使用映射表将字符串类型映射到相应的处理函数，在运行时动态调用处理函数。


*/
namespace UsingRTTI {
class GameObject {
   public:
    virtual void collide(GameObject& otherObject) = 0;
    virtual ~GameObject() = default;
};

class SpaceStation : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        std::cout << "SpaceStation collides with another object" << std::endl;
    }
};

class Asteroid : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        std::cout << "Asteroid collides with another object" << std::endl;
    }
};

class SpaceShip : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        const std::type_info& objectType = typeid(otherObject);
        if (objectType == typeid(SpaceShip)) {
            SpaceShip& ss = static_cast<SpaceShip&>(otherObject);
            std::cout << "SpaceShip collides with another SpaceShip"
                      << std::endl;
        } else if (objectType == typeid(SpaceStation)) {
            std::cout << "SpaceShip collides with SpaceStation" << std::endl;
        } else if (objectType == typeid(Asteroid)) {
            std::cout << "SpaceShip collides with Asteroid" << std::endl;
        }
    }
};
}  // namespace UsingRTTI

namespace UsingVirtualFunctions {
class SpaceShip;  // forward declaration
class SpaceStation;
class Asteroid;

class GameObject {
   public:
    virtual void collide(GameObject& otherObject) = 0;
    virtual void collide(SpaceShip& otherObject) = 0;
    virtual void collide(SpaceStation& otherObject) = 0;
    virtual void collide(Asteroid& otherObject) = 0;
    virtual ~GameObject() = default;
};

class SpaceShip : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        otherObject.collide(*this);
    }
    virtual void collide(SpaceShip& otherObject) override {
        std::cout << "SpaceShip collides with another SpaceShip" << std::endl;
    }
    virtual void collide(SpaceStation& otherObject) override {
        std::cout << "SpaceShip collides with SpaceStation" << std::endl;
    }
    virtual void collide(Asteroid& otherObject) override {
        std::cout << "SpaceShip collides with Asteroid" << std::endl;
    }
};

class SpaceStation : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        otherObject.collide(*this);
    }
    virtual void collide(SpaceShip& otherObject) override {
        std::cout << "SpaceStation collides with SpaceShip" << std::endl;
    }
    virtual void collide(SpaceStation& otherObject) override {
        std::cout << "SpaceStation collides with another SpaceStation"
                  << std::endl;
    }
    virtual void collide(Asteroid& otherObject) override {
        std::cout << "SpaceStation collides with Asteroid" << std::endl;
    }
};

class Asteroid : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        otherObject.collide(*this);
    }
    virtual void collide(SpaceShip& otherObject) override {
        std::cout << "Asteroid collides with SpaceShip" << std::endl;
    }
    virtual void collide(SpaceStation& otherObject) override {
        std::cout << "Asteroid collides with SpaceStation" << std::endl;
    }
    virtual void collide(Asteroid& otherObject) override {
        std::cout << "Asteroid collides with another Asteroid" << std::endl;
    }
};
}  // namespace UsingVirtualFunctions

namespace UsingVirtualFunctionTable {
class GameObject {
   public:
    virtual void collide(GameObject& otherObject) = 0;
    virtual ~GameObject() = default;
};

class SpaceStation : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        std::cout << "SpaceStation collides with another object" << std::endl;
    }
};

class Asteroid : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        std::cout << "Asteroid collides with another object" << std::endl;
    }
};

class SpaceShip : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        otherObject.collide(*this);
    }
    virtual void hitSpaceShip(SpaceShip& otherObject) {
        std::cout << "SpaceShip collides with another SpaceShip" << std::endl;
    }
    virtual void hitSpaceStation(SpaceStation& otherObject) {
        std::cout << "SpaceShip collides with SpaceStation" << std::endl;
    }
    virtual void hitAsteroid(Asteroid& otherObject) {
        std::cout << "SpaceShip collides with Asteroid" << std::endl;
    }
};

}  // namespace UsingVirtualFunctionTable

namespace UsingInitializedVirtualFunctionTable {
class GameObject {
   public:
    virtual void collide(GameObject& otherObject) = 0;
    virtual ~GameObject() = default;
};

class SpaceShip : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        const std::type_info& objectType = typeid(otherObject);
        std::string typeName = objectType.name();

        auto it = collisionMap->find(typeName);
        if (it != collisionMap->end()) {
            (this->*(it->second))(otherObject);
        } else {
            std::cout << "Collision with unknown object type: " << typeName
                      << std::endl;
        }
    }

    virtual void hitSpaceShip(GameObject& spaceShip) {
        std::cout << "SpaceShip collides with another SpaceShip" << std::endl;
    }
    virtual void hitSpaceStation(GameObject& spaceStation) {
        std::cout << "SpaceShip collides with SpaceStation" << std::endl;
    }
    virtual void hitAsteroid(GameObject& asteroid) {
        std::cout << "SpaceShip collides with Asteroid" << std::endl;
    }

    using HitMap = std::map<std::string, void (SpaceShip::*)(GameObject&)>;
    static HitMap* initializeCollisionMap();
    static HitMap* collisionMap;
};

SpaceShip::HitMap* SpaceShip::collisionMap =
    SpaceShip::initializeCollisionMap();

SpaceShip::HitMap* SpaceShip::initializeCollisionMap() {
    HitMap* phm = new HitMap;
    (*phm)["SpaceShip"] = &SpaceShip::hitSpaceShip;
    (*phm)["SpaceStation"] = &SpaceShip::hitSpaceStation;
    (*phm)["Asteroid"] = &SpaceShip::hitAsteroid;
    return phm;
}

class SpaceStation : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        std::cout << "SpaceStation collides with another object" << std::endl;
    }
};

class Asteroid : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override {
        std::cout << "Asteroid collides with another object" << std::endl;
    }
};
}  // namespace UsingInitializedVirtualFunctionTable

void testUsingRTTI() {
    using namespace UsingRTTI;
    SpaceShip ship;
    SpaceStation station;
    Asteroid asteroid;

    ship.collide(station);   // 输出: SpaceShip collides with SpaceStation
    ship.collide(asteroid);  // 输出: SpaceShip collides with Asteroid
    station.collide(
        asteroid);  // 输出: SpaceStation collides with another object
}

void testUsingVirtualFunctions() {
    using namespace UsingVirtualFunctions;
    SpaceShip ship;
    SpaceStation station;
    Asteroid asteroid;

    ship.collide(station);      // 输出: SpaceShip collides with SpaceStation
    ship.collide(asteroid);     // 输出: SpaceShip collides with Asteroid
    station.collide(asteroid);  // 输出: SpaceStation collides with Asteroid
}

void testUsingVirtualFunctionTable() {
    using namespace UsingVirtualFunctionTable;
    SpaceShip ship;
    SpaceStation station;
    Asteroid asteroid;

    ship.collide(station);  // 输出: SpaceStation collides with another object
    ship.collide(asteroid);  // 输出: Asteroid collides with another object
    station.collide(
        asteroid);  // 输出: SpaceStation collides with another object
}

void testUsingInitializedVirtualFunctionTable() {
    using namespace UsingInitializedVirtualFunctionTable;
    SpaceShip ship;
    SpaceStation station;
    Asteroid asteroid;

    ship.collide(station);   // 输出: SpaceShip collides with SpaceStation
    ship.collide(asteroid);  // 输出: SpaceShip collides with Asteroid
    station.collide(
        asteroid);  // 输出: SpaceStation collides with another object
}

int main() {
    std::cout << "Testing Using RTTI:" << std::endl;
    testUsingRTTI();

    std::cout << "\nTesting Using Virtual Functions:" << std::endl;
    testUsingVirtualFunctions();

    std::cout << "\nTesting Using Virtual Function Table:" << std::endl;
    testUsingVirtualFunctionTable();

    std::cout << "\nTesting Using Initialized Virtual Function Table:"
              << std::endl;
    testUsingInitializedVirtualFunctionTable();

    return 0;
}