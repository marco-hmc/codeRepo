#include "vector_wrapper.h"

// 显式实例化 VectorWrapper<int>
template class VectorWrapper<int>;

void func1() {
    VectorWrapper<int> vec;
    vec.add(1);
}