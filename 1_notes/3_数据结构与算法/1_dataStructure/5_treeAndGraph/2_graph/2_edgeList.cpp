#include <iostream>
#include <vector>
using namespace std;

// 边的结构体
struct Edge {
  int src, dest;
};

// 图的类
class Graph {
public:
  // 构造函数
  Graph(const vector<Edge> &edges, int numVertices) {
    // 设置图的顶点数
    this->numVertices = numVertices;

    // 根据边列表构建邻接表
    adjList.resize(numVertices);
    for (const auto &edge : edges) {
      int src = edge.src;
      int dest = edge.dest;

      // 添加边到邻接表
      adjList[src].push_back(dest);
      adjList[dest].push_back(src);
    }
  }

  // 打印图的邻接表
  void printGraph() {
    for (int i = 0; i < numVertices; i++) {
      cout << "顶点 " << i << " 的邻接顶点: ";
      for (const auto &vertex : adjList[i]) {
        cout << vertex << " ";
      }
      cout << endl;
    }
  }

private:
  int numVertices;             // 图的顶点数
  vector<vector<int>> adjList; // 邻接表
};

int main() {
  // 创建边列表
  vector<Edge> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}};

  // 创建图对象
  Graph graph(edges, 5);

  // 打印图的邻接表
  graph.printGraph();

  return 0;
}