#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

class GameObject {
   public:
    virtual void collide(GameObject& otherObject) = 0;
    virtual ~GameObject() = default;
};

class SpaceShip : public GameObject {
   public:
    virtual void collide(GameObject& otherObject) override;
    virtual void hitSpaceShip(GameObject& spaceShip);
    virtual void hitSpaceStation(GameObject& spaceStation);
    virtual void hitAsteroid(GameObject& asteroid);

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

void SpaceShip::collide(GameObject& otherObject) {
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

void SpaceShip::hitSpaceShip(GameObject& spaceShip) {
    std::cout << "SpaceShip collides with another SpaceShip" << std::endl;
}

void SpaceShip::hitSpaceStation(GameObject& spaceStation) {
    std::cout << "SpaceShip collides with SpaceStation" << std::endl;
}

void SpaceShip::hitAsteroid(GameObject& asteroid) {
    std::cout << "SpaceShip collides with Asteroid" << std::endl;
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

void checkForCollision(GameObject& object1, GameObject& object2) {
    object1.collide(object2);
}

int main() {
    SpaceShip ship;
    SpaceStation station;
    Asteroid asteroid;

    checkForCollision(ship,
                      station);  // 输出: SpaceShip collides with SpaceStation
    checkForCollision(ship,
                      asteroid);  // 输出: SpaceShip collides with Asteroid
    checkForCollision(
        station, asteroid);  // 输出: SpaceStation collides with another object

    return 0;
}