/*
1. 一定是成环图。
2. hasNext怎么判断。
3. 约束，参数要深化细节。
4. 迭代顺序问题
*/

#include <functional>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph {
   public:
    Graph(int vertices) : V(vertices) {}

    void addEdge(int src, int dest, double weight) {
        adjList[src].push_back({dest, weight});
    }

    class TopoIterator {
       public:
        TopoIterator(Graph& graph, int start,
                     std::function<bool(int)> stateChecker)
            : graph(graph), stateChecker(stateChecker) {
            visited.clear();
            stack.push({start, graph.adjList[start].begin()});
        }

        bool hasNext() {
            while (!stack.empty()) {
                auto& [v, it] = stack.top();

                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    if (stateChecker(v)) {
                        current = v;
                        return true;
                    }
                }

                bool foundNext = false;
                while (it != graph.adjList[v].end()) {
                    int neighbor = it->first;
                    double weight = it->second;
                    ++it;
                    if (visited.find(neighbor) == visited.end() &&
                        weight > 0.5) {
                        stack.push({neighbor, graph.adjList[neighbor].begin()});
                        foundNext = true;
                        break;
                    }
                }

                if (!foundNext) {
                    stack.pop();
                }
            }

            return false;
        }

        int next() { return current; }

       private:
        Graph& graph;
        int current;
        std::function<bool(int)> stateChecker;
        std::unordered_set<int> visited;
        std::stack<
            std::pair<int, std::vector<std::pair<int, double>>::iterator>>
            stack;
    };

    TopoIterator begin(int start, std::function<bool(int)> stateChecker) {
        return TopoIterator(*this, start, stateChecker);
    }

   private:
    int V;
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjList;
};

int main() {
    Graph g(6);
    g.addEdge(5, 2, 0.6);
    g.addEdge(5, 0, 0.4);
    g.addEdge(4, 0, 0.7);
    g.addEdge(4, 1, 0.8);
    g.addEdge(2, 3, 0.9);
    g.addEdge(3, 1, 0.5);

    /*
    5 → 2 → 3
    ↓   ↓   ↓
    0   3 → 1
    ↓
    4 → 1
    */

    auto stateChecker = [](int v) { return v % 2 == 0; };

    std::cout << "Topological Sort starting from vertex 5:\n";
    auto it = g.begin(5, stateChecker);
    while (it.hasNext()) {
        int v = it.next();
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}