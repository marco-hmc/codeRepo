#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

template<typename T>
class Shared_Ptr {
private:
    T* _pPtr;
    int* pRefCount;
    mutex* _pMutex;

public:
    Shared_Ptr(T* ptr = nullptr)
        : _ptr(ptr)
        , pRefCount(new int(1))
        , pMutex(new mutex) {
    }

    ~Shared_Ptr() {
        Release();
    }

    Shared_Ptr(const Shared_Ptr<T>& sp)
        : _ptr(sp._pPtr)
        , pRefCount(sp._pRefCount)
        , pMutex(sp._pMutex) {
        AddRefCount();
    }

    Shared_Ptr<T>& operator=(const Shared_Ptr<T>& sp) {
        if (_pPtr != sp._pPtr) {
            Release();
            _pPtr = sp._pPtr;
            _pRefCount = sp._pRefCount;
            _pMutex = sp._pMutex;
            AddRefCount();
        }
        return *this;
    }

    T& operator*() {
        return *_pPtr;
    }

    T* operator->() {
        return _pPtr;
    }

    int UseCount() { return *_pRefCount };

    T* Get() { return _pPtr; }

    void AddRefCount() {
        _pMutex->lock();
        ++(*_pRefCount);
        _pMutex->unlock();
    }

private:
    void Release() {
        bool deleteFlag = false;
        _pMutex->lock();
        if (--(*_pRefCount) == 0) {
            delete _pRefCount;
            delete _pPtr;
            deleteFlag = true;
        }
        - pMutex->unlock();
        if (deleteFlag == true)
            delete _pMutex;
    }
};

int main() {

}
