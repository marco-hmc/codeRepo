
#include <functional>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
    using ID = std::string;

    struct Data {
        int value;
        bool operator==(const Data& rhs) const { return value == rhs.value; }
    };

    struct RelationParam {
        int value;
    };

    class Node {
      public:
        explicit Node(ID id) : id(id) {}
        ID getId() const { return id; }

        void addFromNode(ID from) { fromNode.push_back(from); }
        void addToNode(ID to) { toNode.push_back(to); }

        std::vector<ID> getFromNode() const { return fromNode; }
        std::vector<ID> getToNode() const { return toNode; }

      protected:
        ID id;
        std::vector<ID> fromNode;
        std::vector<ID> toNode;
    };

    class DataNode : public Node {
      public:
        explicit DataNode(ID id) : Node(id) {}
        Data getData() const { return data; }
        Data& getData() { return data; }

      private:
        Data data{};
    };

    Node* getNodeById(ID id) {
        id;
        return nullptr;
    }

    class RelationNode : public Node {
      public:
        explicit RelationNode(ID id) : Node(id) {}
        void setRelationFunc(std::function<bool(Node*)> func) {
            m_relationFunc = std::move(func);
        }
        std::function<bool(Node*)> relationFunc() const {
            return m_relationFunc;
        }

      private:
        std::vector<Node*> targetNode;
        RelationParam param;
        std::function<bool(Node*)> m_relationFunc;
    };

}  // namespace

class Iterator {
  public:
    explicit Iterator(Node* startNode) : currentNode(startNode) {}

    // 计算当前obj受到约束时是否发生变化，如果变化的值是多少
    bool perform() {
        auto oldData = static_cast<DataNode*>(currentNode)->getData();
        calculate();
        auto currentData = static_cast<DataNode*>(currentNode)->getData();
        const bool isChanged = oldData == currentData;
        return isChanged;
    }

    bool hasNext() {}

    void next() {}

  private:
    bool calculate() {
        const auto& fromRelations = currentNode->getFromNode();
        for (const auto& fromRelation : fromRelations) {
            // Assuming you have a way to get the RelationNode* from an ID
            auto* relationNode =
                static_cast<RelationNode*>(getNodeById(fromRelation));
            bool isSuccess = relationNode->relationFunc()(currentNode);
            if (!isSuccess) {
                return false;
            }
        }
        return true;
    }

  private:
    Node* currentNode;
    std::unordered_set<ID> visited;  // 历史访问顺序
    std::stack<Node*> stack;         // 上一个分叉节点
};

int main() {
    // A<-->1<-->B<-->2<-->C<-->3<-->A
    DataNode A("A");
    DataNode B("B");
    DataNode C("C");
    RelationNode r1("1");
    r1.setRelationFunc([](Node* node) {
        auto* dataNode = static_cast<DataNode*>(node);
        dataNode->getData().value += 1;
        return true;
    });
    RelationNode r2("2");
    r2.setRelationFunc([](Node* node) { return true; });
    RelationNode r3("3");
    r3.setRelationFunc([](Node* node) { return true; });

    A.addToNode(r1.getId());
    r1.addFromNode(A.getId());
    r1.addToNode(B.getId());
    B.addFromNode(r1.getId());
    B.addToNode(r2.getId());
    r2.addFromNode(B.getId());
    r2.addToNode(C.getId());
    C.addFromNode(r2.getId());
    C.addToNode(r3.getId());
    r3.addFromNode(C.getId());
    r3.addToNode(A.getId());
    A.addFromNode(r3.getId());

    Iterator dataIterator(&A);
    while (dataIterator.hasNext()) {
        bool isChanged = dataIterator.perform();
        if (!isChanged) {
            break;
        }
        dataIterator.next();
    }
    return 0;
}