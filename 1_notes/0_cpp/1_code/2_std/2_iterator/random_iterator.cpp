#include <iostream>
#include <vector>

template <typename T> class RandomIterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  RandomIterator(T *ptr) : m_ptr(ptr) {}

  reference operator*() const { return *m_ptr; }

  pointer operator->() const { return m_ptr; }

  RandomIterator &operator++() {
    ++m_ptr;
    return *this;
  }

  RandomIterator operator++(int) {
    RandomIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  RandomIterator &operator--() {
    --m_ptr;
    return *this;
  }

  RandomIterator operator--(int) {
    RandomIterator tmp = *this;
    --(*this);
    return tmp;
  }

  RandomIterator &operator+=(difference_type n) {
    m_ptr += n;
    return *this;
  }

  RandomIterator operator+(difference_type n) const {
    RandomIterator tmp = *this;
    return tmp += n;
  }

  RandomIterator &operator-=(difference_type n) { return *this += -n; }

  RandomIterator operator-(difference_type n) const {
    RandomIterator tmp = *this;
    return tmp -= n;
  }

  difference_type operator-(const RandomIterator &other) const {
    return m_ptr - other.m_ptr;
  }

  reference operator[](difference_type n) const { return *(m_ptr + n); }

  bool operator==(const RandomIterator &other) const {
    return m_ptr == other.m_ptr;
  }

  bool operator!=(const RandomIterator &other) const {
    return !(*this == other);
  }

  bool operator<(const RandomIterator &other) const {
    return m_ptr < other.m_ptr;
  }

  bool operator>(const RandomIterator &other) const { return other < *this; }

  bool operator<=(const RandomIterator &other) const {
    return !(other < *this);
  }

  bool operator>=(const RandomIterator &other) const {
    return !(*this < other);
  }

private:
  T *m_ptr;
};

int main() {
  std::vector<int> vec = {1, 2, 3, 4, 5};

  RandomIterator<int> begin(vec.data());
  RandomIterator<int> end(vec.data() + vec.size());

  for (RandomIterator<int> it = begin; it != end; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  return 0;
}