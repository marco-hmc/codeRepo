#include <iostream>
#include <vector>

using namespace std;

// 定义图的数据结构
class Graph {
private:
    int numVertices; // 图中顶点的数量
    vector<vector<int>> adjLists; // 邻接表表示的图

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjLists.resize(vertices);
    }

    // 添加边
    void addEdge(int src, int dest) {
        adjLists[src].push_back(dest);
    }

    // DFS遍历
    void DFS(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        // 遍历当前节点的邻接节点
        for (int adjVertex : adjLists[vertex]) {
            if (!visited[adjVertex]) {
                DFS(adjVertex, visited);
            }
        }
    }

    // 对外接口,开始DFS遍历
    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        DFS(startVertex, visited);
    }
};

int main() {
    // 创建一个包含5个顶点的图
    Graph graph(5);

    // 添加边
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);

    cout << "DFS遍历结果:" << endl;
    graph.DFS(0);

    return 0;
}
