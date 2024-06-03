#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 定义图的邻接表表示
class Graph {
private:
    int numVertices; // 图中顶点的数量
    vector<vector<int>> adjLists; // 邻接表

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjLists.resize(vertices);
    }

    // 添加边
    void addEdge(int src, int dest) {
        adjLists[src].push_back(dest);
        adjLists[dest].push_back(src);
    }

    // BFS遍历
    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false); // 记录顶点是否被访问过
        queue<int> queue; // 用于BFS的队列

        visited[startVertex] = true;
        queue.push(startVertex);

        while (!queue.empty()) {
            int currVertex = queue.front();
            cout << currVertex << " ";
            queue.pop();

            // 遍历当前顶点的所有邻接顶点
            for (int adjVertex : adjLists[currVertex]) {
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    queue.push(adjVertex);
                }
            }
        }
    }
};

int main() {
  // 创建一个包含6个顶点的图
  Graph graph(6);

  // 添加边
  graph.addEdge(0, 1);
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 4);
  graph.addEdge(3, 4);
  graph.addEdge(3, 5);
  graph.addEdge(4, 5);

  cout << "BFS遍历结果: ";
  graph.BFS(0);

  return 0;
}
