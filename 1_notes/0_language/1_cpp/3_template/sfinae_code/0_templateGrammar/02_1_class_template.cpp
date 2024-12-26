#include <cassert>
#include <deque>
#include <string>

namespace jc {
    template <typename T,
              template <typename Elem, typename = std::allocator<Elem>>
              class Container = std::deque>
    class Stack {
      public:
        using reference = T&;
        using const_reference = const T&;

        template <typename, template <typename, typename> class>
        friend class Stack;

        template <typename U,
                  template <typename Elem2, typename = std::allocator<Elem2>>
                  class Container2>
        Stack<T, Container>& operator=(const Stack<U, Container2>& /*rhs*/);

        void push(const T& /*x*/);

        void pop();

        reference top();

        const_reference top() const;

        std::size_t size() const;

        bool empty() const;

      private:
        Container<T> container_;
    };

    template <typename T, template <typename, typename> class Container>
    template <typename U, template <typename, typename> class Container2>
    inline Stack<T, Container>& Stack<T, Container>::operator=(
        const Stack<U, Container2>& rhs) {
        container_.assign(rhs.container_.begin(), rhs.container_.end());
        return *this;
    }

    template <typename T, template <typename, typename> class Container>
    inline void Stack<T, Container>::push(const T& x) {
        container_.emplace_back(x);
    }

    template <typename T, template <typename, typename> class Container>
    inline void Stack<T, Container>::pop() {
        assert(!empty());
        container_.pop_back();
    }

    template <typename T, template <typename, typename> class Container>
    inline typename Stack<T, Container>::reference Stack<T, Container>::top() {
        assert(!empty());
        return container_.back();
    }

    template <typename T, template <typename, typename> class Container>
    inline typename Stack<T, Container>::const_reference
    Stack<T, Container>::top() const {
        assert(!empty());
        return container_.back();
    }

    template <typename T, template <typename, typename> class Container>
    inline std::size_t Stack<T, Container>::size() const {
        return container_.size();
    }

    template <typename T, template <typename, typename> class Container>
    inline bool Stack<T, Container>::empty() const {
        return container_.empty();
    }

}  // namespace jc

int main() {
    jc::Stack<std::string, std::deque> s;
    s.push("hello");
    s.push("world");
    assert(s.size() == 2);
    assert(s.top() == "world");
    s.pop();
    assert(s.size() == 1);
    assert(s.top() == "hello");
    s.pop();
    assert(s.empty());
}
