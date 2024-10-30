#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class PathNode {
   public:
 std::unordered_map<std::string, std::shared_ptr<PathNode>> children;
 bool isEndOfPath = false;
};

class PathCacheTree {
   public:
    PathCacheTree() : root(std::make_shared<PathNode>()) {}

    void insert(const std::string& path) {
        auto currentNode = root;
        size_t pos = 0, found;
        while ((found = path.find('/', pos)) != std::string::npos) {
            std::string part = path.substr(pos, found - pos);
            if (!currentNode->children.count(part)) {
                currentNode->children[part] = std::make_shared<PathNode>();
            }
            currentNode = currentNode->children[part];
            pos = found + 1;
        }
        std::string part = path.substr(pos);
        if (!currentNode->children.count(part)) {
            currentNode->children[part] = std::make_shared<PathNode>();
        }
        currentNode->children[part]->isEndOfPath = true;
    }

    bool search(const std::string& path) const {
        auto currentNode = root;
        size_t pos = 0, found;
        while ((found = path.find('/', pos)) != std::string::npos) {
            std::string part = path.substr(pos, found - pos);
            if (!currentNode->children.count(part)) {
                return false;
            }
            currentNode = currentNode->children.at(part);
            pos = found + 1;
        }
        std::string part = path.substr(pos);
        return currentNode->children.count(part) &&
               currentNode->children.at(part)->isEndOfPath;
    }

   private:
    std::shared_ptr<PathNode> root;
};

int main() {
    PathCacheTree tree;
    tree.insert("/home/user/documents");
    tree.insert("/home/user/pictures");

    std::cout << std::boolalpha;
    std::cout << "Search /home/user/documents: "
              << tree.search("/home/user/documents") << std::endl;
    std::cout << "Search /home/user/music: " << tree.search("/home/user/music")
              << std::endl;

    return 0;
}