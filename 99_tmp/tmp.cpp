

template <typename T> class unique_ptr {
public:
  explicit unique_ptr(T *ptr = nullptr) : m_ptr(ptr) {}

  ~unique_ptr() { delete m_ptr; }

  unique_ptr(const unique_ptr &) = delete;

  unique_ptr &operator=(const unique_ptr &) = delete;

  unique_ptr(unique_ptr &&other) : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }

  unique_ptr &operator=(unique_ptr &&other) {
    if (this != &other) {
      delete m_ptr;
      m_ptr = other.m_ptr;
      other.m_ptr = nullptr;
    }
    return *this;
  }

  void reset(T *ptr = nullptr) {
    delete m_ptr;
    m_ptr = ptr;
  }

  T *get() const { return m_ptr; }

private:
  T *m_ptr;
};

int main() {}