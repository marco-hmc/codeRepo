#include <iostream>
#include <vector>

enum class Status { UNVISITED, VISITING, VISITED };

bool hasCycleDFS(int node, std::vector<std::vector<int>> &graph,
                 std::vector<Status> &status) {
  status[node] = Status::VISITING;
  for (int neighbor : graph[node]) {
    if (status[neighbor] == Status::VISITING) {
      return true;
    }
    if (status[neighbor] == Status::UNVISITED &&
        hasCycleDFS(neighbor, graph, status)) {
      return true;
    }
  }
  status[node] = Status::VISITED;
  return false;
}

bool hasCycle(int numNodes, std::vector<std::vector<int>> &graph) {
  std::vector<Status> status(numNodes, Status::UNVISITED);
  for (int i = 0; i < numNodes; ++i) {
    if (status[i] == Status::UNVISITED && hasCycleDFS(i, graph, status)) {
      return true;
    }
  }
  return false;
}

int main() {
  // Test case 1: Graph with a cycle
  std::vector<std::vector<int>> graph1 = {{1, 2}, {2, 3}, {3, 1}};
  std::cout << "start" << std::endl;
  std::cout << (hasCycle(4, graph1) ? "Graph contains a cycle\n"
                                    : "Graph doesn't contain a cycle\n");

  // Test case 2: Graph without a cycle
  std::vector<std::vector<int>> graph2 = {{1, 2}, {2, 3}, {3, 4}};
  std::cout << (hasCycle(5, graph2) ? "Graph contains a cycle\n"
                                    : "Graph doesn't contain a cycle\n");

  return 0;
}