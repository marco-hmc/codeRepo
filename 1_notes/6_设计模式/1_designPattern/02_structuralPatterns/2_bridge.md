桥接模式（Bridge Pattern）是一种设计模式，它通过将抽象部分与实现部分分离，使它们可以独立地变化。具体来说，桥接模式使用组合而不是继承来连接抽象部分和实现部分。

```c++
#include <iostream>
#include <memory>

// 实现部分接口
class Color {
   public:
    virtual ~Color() = default;
    virtual std::string Fill() const = 0;
};

// 具体实现部分
class RedColor : public Color {
   public:
    std::string Fill() const override { return "Color is Red"; }
};

class BlueColor : public Color {
   public:
    std::string Fill() const override { return "Color is Blue"; }
};

// 抽象部分接口
class Shape {
   protected:
    std::shared_ptr<Color> color;

   public:
    Shape(std::shared_ptr<Color> color) : color(color) {}
    virtual ~Shape() = default;
    virtual void Draw() const = 0;
};

// 具体抽象部分
class Circle : public Shape {
   private:
    int radius;

   public:
    Circle(int radius, std::shared_ptr<Color> color)
        : Shape(color), radius(radius) {}
    void Draw() const override {
        std::cout << "Circle with radius " << radius << " and " << color->Fill()
                  << std::endl;
    }
};

class Rectangle : public Shape {
   private:
    int width, height;

   public:
    Rectangle(int width, int height, std::shared_ptr<Color> color)
        : Shape(color), width(width), height(height) {}
    void Draw() const override {
        std::cout << "Rectangle with width " << width << " and height "
                  << height << " and " << color->Fill() << std::endl;
    }
};

int main() {
    std::shared_ptr<Color> red = std::make_shared<RedColor>();
    std::shared_ptr<Color> blue = std::make_shared<BlueColor>();

    std::shared_ptr<Shape> circle = std::make_shared<Circle>(10, red);
    std::shared_ptr<Shape> rectangle =
        std::make_shared<Rectangle>(20, 30, blue);

    circle->Draw();
    rectangle->Draw();

    return 0;
}
```