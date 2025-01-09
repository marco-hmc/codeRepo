#include <mutex>

class some_data {
    int a;
    std::string b;

  public:
    void do_something() {}
};

class data_wrapper {
  private:
    some_data data;
    std::mutex m;

  public:
    template <typename Function>
    void process_data(Function func) {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }

    template <typename Function>
    void safe_process_data(Function func) {
        std::lock_guard<std::mutex> l(m);
        some_data data_copy = data;
        func(data_copy);
        data = data_copy;
    }
};

some_data* unprotected;

void malicious_function(some_data& protected_data) {
    unprotected = &protected_data;
}

void foo() {
    data_wrapper x;
    x.process_data(malicious_function);
    unprotected->do_something();
}

int main() { foo(); }
