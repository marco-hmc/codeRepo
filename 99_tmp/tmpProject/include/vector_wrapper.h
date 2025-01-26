#ifndef VECTOR_WRAPPER_H
#define VECTOR_WRAPPER_H

#include <vector>

template <typename T>
class VectorWrapper {
  public:
    void add(const T& value) { vec.push_back(value); }
    const T& get(int index) const { return vec[index]; }

  private:
    std::vector<T> vec;
};

// 声明显式实例化
extern template class VectorWrapper<int>;

#endif  // VECTOR_WRAPPER_H