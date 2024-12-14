#include <iostream>
#include <string>
#include <vector>

class Visitor;

// Element interface
class Element {
  public:
    virtual ~Element() {}
    virtual void accept(Visitor &visitor) = 0;
};

// Concrete Elements
class ConcreteElementA : public Element {
  public:
    void accept(Visitor &visitor) override;
    std::string operationA() const { return "ConcreteElementA"; }
};

class ConcreteElementB : public Element {
  public:
    void accept(Visitor &visitor) override;
    std::string operationB() const { return "ConcreteElementB"; }
};

// Visitor interface
class Visitor {
  public:
    virtual ~Visitor() {}
    virtual void visitConcreteElementA(ConcreteElementA *element) = 0;
    virtual void visitConcreteElementB(ConcreteElementB *element) = 0;
};

// Concrete Visitors
class ConcreteVisitor1 : public Visitor {
  public:
    void visitConcreteElementA(ConcreteElementA *element) override {
        std::cout << "ConcreteVisitor1: " << element->operationA() << std::endl;
    }
    void visitConcreteElementB(ConcreteElementB *element) override {
        std::cout << "ConcreteVisitor1: " << element->operationB() << std::endl;
    }
};

class ConcreteVisitor2 : public Visitor {
  public:
    void visitConcreteElementA(ConcreteElementA *element) override {
        std::cout << "ConcreteVisitor2: " << element->operationA() << std::endl;
    }
    void visitConcreteElementB(ConcreteElementB *element) override {
        std::cout << "ConcreteVisitor2: " << element->operationB() << std::endl;
    }
};

// Implement accept methods
void ConcreteElementA::accept(Visitor &visitor) {
    visitor.visitConcreteElementA(this);
}

void ConcreteElementB::accept(Visitor &visitor) {
    visitor.visitConcreteElementB(this);
}

// Client code
void clientCode(std::vector<Element *> &elements, Visitor &visitor) {
    for (Element *element : elements) {
        element->accept(visitor);
    }
}

int main() {
    std::vector<Element *> elements = {new ConcreteElementA(),
                                       new ConcreteElementB()};
    ConcreteVisitor1 visitor1;
    ConcreteVisitor2 visitor2;

    std::cout << "Using ConcreteVisitor1:" << std::endl;
    clientCode(elements, visitor1);

    std::cout << "Using ConcreteVisitor2:" << std::endl;
    clientCode(elements, visitor2);

    for (Element *element : elements) {
        delete element;
    }

    return 0;
}