#include <iostream>

template <typename T> class UniquePtr {
private:
  T *ptr;

public:
  explicit UniquePtr(T *p = nullptr) : ptr(p) {}

  ~UniquePtr() { delete ptr; }

  UniquePtr(const UniquePtr &) = delete;
  UniquePtr &operator=(const UniquePtr &) = delete;

  UniquePtr(UniquePtr &&other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
  }

  UniquePtr &operator=(UniquePtr &&other) noexcept {
    if (this != &other) {
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }

  T &operator*() const { return *ptr; }

  T *operator->() const { return ptr; }

  T *get() const { return ptr; }

  void reset(T *p = nullptr) {
    delete ptr;
    ptr = p;
  }
};

int main() {
  // 创建一个UniquePtr来管理一个整型对象
  UniquePtr<int> ptr(new int(42));

  // 使用UniquePtr访问所管理的对象
  std::cout << "Value: " << *ptr << std::endl;

  // 修改所管理的对象的值
  *ptr = 100;

  // 再次使用UniquePtr访问所管理的对象
  std::cout << "Value: " << *ptr << std::endl;

  // 释放UniquePtr所管理的对象
  ptr.reset();

  // 尝试访问已释放的对象会导致运行时错误
  // std::cout << "Value: " << *ptr << std::endl;

  return 0;
}

// template<typename T>
// class UniquePtr{
// public:
// 	UniquePtr(T *pResource = NULL)
// 		: m_pResource(pResource) { }

// 	~UniquePtr() {
// 		del();
// 	}

// public:
// 	void reset(T* pResource) // 先释放资源(如果持有), 再持有资源
// 	{
// 		del();
// 		m_pResource = pResource;
// 	}

// 	T* release() // 返回资源,资源的释放由调用方处理
// 	{
// 		T* pTemp = m_pResource;
// 		m_pResource = nullptr;
// 		return pTemp;
// 	}

// 	T* get() // 获取资源,调用方应该只使用不释放,否则会两次delete资源
// 	{
// 		return m_pResource;
// 	}

// public:
// 	operator bool() const // 是否持有资源
// 	{
// 		return m_pResource != nullptr;
// 	}

// 	T& operator * ()
// 	{
// 		return *m_pResource;
// 	}

// 	T* operator -> ()
// 	{
// 		return m_pResource;
// 	}

// private:
// 	void del()
// 	{
// 		if (!m_pResource) return;
// 		delete m_pResource;
// 		m_pResource = nullptr;
// 	}

// private:
// 	UniquePtr(const UniquePtr &) = delete; // 禁用拷贝构造
// 	UniquePtr& operator = (const UniquePtr &) = delete; // 禁用拷贝赋值

// private:
// 	T *m_pResource;
// };
