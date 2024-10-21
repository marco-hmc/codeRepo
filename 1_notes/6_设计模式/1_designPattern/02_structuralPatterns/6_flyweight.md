假设我们有一个绘图应用程序，需要绘制大量的圆形。每个圆形都有颜色、位置和半径等属性。为了减少内存使用，我们可以将颜色作为共享的部分，而位置和半径作为非共享的部分。

```c++
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// 享元接口
class Shape {
   public:
    virtual void draw(int x, int y, int radius) = 0;
};

// 具体享元类
class Circle : public Shape {
   private:
    std::string color;

   public:
    Circle(const std::string& color) : color(color) {}

    void draw(int x, int y, int radius) override {
        std::cout << "Drawing Circle [Color: " << color << ", x: " << x
                  << ", y: " << y << ", radius: " << radius << "]" << std::endl;
    }
};

// 享元工厂类
class ShapeFactory {
   private:
    std::unordered_map<std::string, Shape*> circleMap;

   public:
    ~ShapeFactory() {
        for (auto& pair : circleMap) {
            delete pair.second;
        }
    }

    Shape* getCircle(const std::string& color) {
        if (circleMap.find(color) == circleMap.end()) {
            circleMap[color] = new Circle(color);
            std::cout << "Creating Circle of color: " << color << std::endl;
        }
        return circleMap[color];
    }
};

// 客户端代码
int main() {
    ShapeFactory* shapeFactory = new ShapeFactory();

    std::vector<std::string> colors = {"Red", "Green", "Blue",
                                       "Red", "Green", "Blue"};

    for (const auto& color : colors) {
        Shape* circle = shapeFactory->getCircle(color);
        circle->draw(rand() % 100, rand() % 100, rand() % 50);
    }

    delete shapeFactory;
    return 0;
}
```