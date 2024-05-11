#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>


// 定义贪吃蛇的方向
enum class Direction { UP, DOWN, LEFT, RIGHT };

// 定义贪吃蛇的节点
struct SnakeNode {
  int x;
  int y;
  SnakeNode(int x, int y) : x(x), y(y) {}
};

// 定义贪吃蛇类
class SnakeGame {
private:
  int width;
  int height;
  std::vector<SnakeNode> snake;
  SnakeNode food;
  Direction direction;

public:
  SnakeGame(int width, int height) : width(width), height(height) {
    // 初始化贪吃蛇的位置和方向
    snake.push_back(SnakeNode(width / 2, height / 2));
    direction = Direction::UP;

    // 随机生成食物的位置
    srand(time(nullptr));
    food.x = rand() % width;
    food.y = rand() % height;
  }

  // 更新贪吃蛇的位置和食物的位置
  void update() {
    // TODO: 实现蒙特卡洛树搜索算法来决定下一步的方向

    // 随机选择一个方向
    int randomDirection = rand() % 4;
    switch (randomDirection) {
    case 0:
      direction = Direction::UP;
      break;
    case 1:
      direction = Direction::DOWN;
      break;
    case 2:
      direction = Direction::LEFT;
      break;
    case 3:
      direction = Direction::RIGHT;
      break;
    }

    // 根据方向更新贪吃蛇的位置
    SnakeNode head = snake.front();
    switch (direction) {
    case Direction::UP:
      snake.insert(snake.begin(), SnakeNode(head.x, head.y - 1));
      break;
    case Direction::DOWN:
      snake.insert(snake.begin(), SnakeNode(head.x, head.y + 1));
      break;
    case Direction::LEFT:
      snake.insert(snake.begin(), SnakeNode(head.x - 1, head.y));
      break;
    case Direction::RIGHT:
      snake.insert(snake.begin(), SnakeNode(head.x + 1, head.y));
      break;
    }

    // 如果贪吃蛇吃到了食物,则生成新的食物
    if (snake.front().x == food.x && snake.front().y == food.y) {
      food.x = rand() % width;
      food.y = rand() % height;
    } else {
      // 如果贪吃蛇没有吃到食物,则删除尾部节点
      snake.pop_back();
    }
  }

  // 打印贪吃蛇和食物的位置
  void print() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        if (x == food.x && y == food.y) {
          std::cout << "*";
        } else {
          bool isSnakeNode = false;
          for (const auto &node : snake) {
            if (node.x == x && node.y == y) {
              isSnakeNode = true;
              break;
            }
          }
          if (isSnakeNode) {
            std::cout << "O";
          } else {
            std::cout << ".";
          }
        }
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  // 创建贪吃蛇游戏对象
  SnakeGame game(20, 10);

  // 游戏循环
  while (true) {
    // 更新贪吃蛇的位置和食物的位置
    game.update();

    // 打印贪吃蛇和食物的位置
    game.print();

    // 延时一段时间
    // TODO: 可以根据需要调整延时的时间
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  return 0;
}