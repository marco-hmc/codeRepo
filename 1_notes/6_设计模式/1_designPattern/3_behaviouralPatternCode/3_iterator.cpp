#include <iostream>
#include <memory>
#include <vector>

// 迭代器接口
template <typename T>
class Iterator {
  public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

// 数字集合类
class NumberCollection {
  public:
    void add(int number) { numbers_.push_back(number); }

    std::unique_ptr<Iterator<int>> createIterator() const {
        return std::make_unique<NumberIterator>(*this);
    }

  private:
    std::vector<int> numbers_;

    // 内部迭代器类
    class NumberIterator : public Iterator<int> {
      public:
        NumberIterator(const NumberCollection& collection)
            : collection_(collection), index_(0) {}

        bool hasNext() const override {
            return index_ < collection_.numbers_.size();
        }

        int next() override { return collection_.numbers_[index_++]; }

      private:
        const NumberCollection& collection_;
        size_t index_;
    };
};

int main() {
    NumberCollection collection;
    collection.add(1);
    collection.add(2);
    collection.add(3);

    auto iterator = collection.createIterator();
    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }
    std::cout << std::endl;  // 输出: 1 2 3

    return 0;
}