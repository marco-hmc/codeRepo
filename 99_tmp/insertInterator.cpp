#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename Container>
class back_insert_iterator {
   protected:
    Container* container;

   public:
    using iterator_category = std::output_iterator_tag;
    using container_value_type = typename std::remove_reference<
        decltype(*std::declval<Container>().begin())>::type;

    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    explicit back_insert_iterator(Container& c) : container(&c) {}

    back_insert_iterator& operator=(const container_value_type& value) {
        container->append(value);
        return *this;
    }

    back_insert_iterator& operator=(container_value_type&& value) {
        container->append(std::move(value));
        return *this;
    }

    back_insert_iterator& operator*() { return *this; }
    back_insert_iterator& operator++() { return *this; }
    back_insert_iterator& operator++(int) { return *this; }
};

template <typename Container>
back_insert_iterator<Container> back_inserter(Container& c) {
    return back_insert_iterator<Container>(c);
}

// 自定义容器类
template <typename T>
class CustomContainer {
   public:
    using value_type = T;

    void append(const T& value) { data.push_back(value); }

    void print() const {
        for (const auto& elem : data) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

   public:
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }

   private:
    std::vector<T> data;
};

int main() {
    CustomContainer<int> container;
    for (const auto& elem : container) {
        std::cout << elem << " ";
    }

    std::cout << std::endl << " --- " << std::endl;

    std::vector<int> values = {1, 2, 3, 4, 5};
    std::copy(values.begin(), values.end(), back_inserter(container));

    for (const auto& elem : container) {
        std::cout << elem << " ";
    }

    return 0;
}