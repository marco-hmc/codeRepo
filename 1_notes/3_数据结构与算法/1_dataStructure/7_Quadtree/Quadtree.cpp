#include <iostream>
#include <memory>
#include <vector>

// 表示二维空间中的点
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// 表示二维空间中的矩形区域
struct Rect {
    double x, y, width, height;
    Rect(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height) {}

    // 检查点是否在矩形区域内
    bool contains(const Point& point) const {
        return point.x >= x && point.x <= x + width && point.y >= y &&
               point.y <= y + height;
    }

    // 检查矩形区域是否与另一个矩形区域相交
    bool intersects(const Rect& other) const {
        return other.x <= x + width && other.x + other.width >= x &&
               other.y <= y + height && other.y + other.height >= y;
    }
};

// 四叉树节点
class Quadtree {
  public:
    Quadtree(const Rect& boundary, int capacity)
        : boundary(boundary), capacity(capacity), divided(false) {}

    // 插入点到四叉树中
    bool insert(const Point& point) {
        if (!boundary.contains(point)) {
            return false;
        }

        if (points.size() < capacity) {
            points.push_back(point);
            return true;
        } else {
            if (!divided) {
                subdivide();
            }
            if (northwest->insert(point)) return true;
            if (northeast->insert(point)) return true;
            if (southwest->insert(point)) return true;
            if (southeast->insert(point)) return true;
        }
        return false;
    }

    // 查询矩形区域内的所有点
    void query(const Rect& range, std::vector<Point>& found) const {
        if (!boundary.intersects(range)) {
            return;
        }

        for (const auto& point : points) {
            if (range.contains(point)) {
                found.push_back(point);
            }
        }

        if (divided) {
            northwest->query(range, found);
            northeast->query(range, found);
            southwest->query(range, found);
            southeast->query(range, found);
        }
    }

  private:
    Rect boundary;
    int capacity;
    std::vector<Point> points;
    bool divided;
    std::unique_ptr<Quadtree> northwest, northeast, southwest, southeast;

    // 将当前节点划分为四个子节点
    void subdivide() {
        double x = boundary.x;
        double y = boundary.y;
        double w = boundary.width / 2;
        double h = boundary.height / 2;

        northwest = std::make_unique<Quadtree>(Rect(x, y, w, h), capacity);
        northeast = std::make_unique<Quadtree>(Rect(x + w, y, w, h), capacity);
        southwest = std::make_unique<Quadtree>(Rect(x, y + h, w, h), capacity);
        southeast =
            std::make_unique<Quadtree>(Rect(x + w, y + h, w, h), capacity);

        divided = true;
    }
};

int main() {
    // 定义四叉树的边界和容量
    Rect boundary(0, 0, 200, 200);
    Quadtree qt(boundary, 4);

    // 插入一些点
    qt.insert(Point(50, 50));
    qt.insert(Point(150, 150));
    qt.insert(Point(100, 100));
    qt.insert(Point(75, 75));
    qt.insert(Point(125, 125));

    // 查询某个范围内的点
    Rect range(50, 50, 100, 100);
    std::vector<Point> found;
    qt.query(range, found);

    // 输出查询结果
    std::cout << "Points found: " << found.size() << std::endl;
    for (const auto& point : found) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }

    return 0;
}