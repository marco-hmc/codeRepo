// template <typename T> class RemovePointer<T *> {
// public:
//   // 如果是传进来的是一个指针，我们就剥夺一层，直到指针形式不存在为止。
//   // 例如 RemovePointer<int**>，Result 是 RemovePointer<int*>::Result，
//   // 而 RemovePointer<int*>::Result 又是 int，最终就变成了我们想要的
//   // int，其它也是类似。
//   typedef typename RemovePointer<T>::Result Result;
// };
