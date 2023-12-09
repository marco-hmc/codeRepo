template<typename T>
class SmartPtr {
private:
    T* ptr;
    int* count;
public:
    SmartPtr(/* args */);
    ~SmartPtr();
};

template<typename T>
SmartPtr<T>::SmartPtr(/* args */) {
}
template<typename T>
SmartPtr<T>::~SmartPtr() {
}
