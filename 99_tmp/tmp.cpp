template <typename FuncType> class Function {

  template <typename ReturnType, typename... ArgTypes>
  inline bool operator==(decltype(nullptr),
                         const Function<ReturnType(ArgTypes)> &func) noexcept {
    return !func;
  }
};

int main() {
  Function<void(int)> f;
  f = nullptr;
  return 0;
}
