假设我们有一个图像查看器应用程序，需要加载和显示图像。为了提高性能，我们可以使用代理模式来延迟图像的加载，直到真正需要显示图像时才进行加载。

```c++
#include <iostream>
#include <string>

// 图像接口
class Image {
   public:
 virtual void display() const = 0;
};

// 具体图像类
class RealImage : public Image {
   private:
    std::string filename;

    void loadFromDisk() const {
        std::cout << "Loading " << filename << std::endl;
    }

   public:
 RealImage(const std::string& filename) : filename(filename) { loadFromDisk(); }

 void display() const override {
     std::cout << "Displaying " << filename << std::endl;
    }
};

// 代理图像类
class ProxyImage : public Image {
   private:
    std::string filename;
    RealImage* realImage;

   public:
    ProxyImage(const std::string& filename)
        : filename(filename), realImage(nullptr) {}

    ~ProxyImage() { delete realImage; }

    void display() const override {
        if (realImage == nullptr) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
};

// 客户端代码
int main() {
    Image* image1 = new ProxyImage("image1.jpg");
    Image* image2 = new ProxyImage("image2.jpg");

    // 图像将会在第一次调用 display() 时加载
    image1->display();
    image2->display();

    // 图像已经加载，不会再次加载
    image1->display();

    delete image1;
    delete image2;

    return 0;
}
```