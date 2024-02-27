```c++
    // `unsigned long long` parameter required for integer literal.
    long long
    operator"" _celsius(unsigned long long tempCelsius) {
  return std::llround(tempCelsius * 1.8 + 32);
}
24_celsius; // == 75
```

    String to integer conversion :
```c++
    // `const char*` and `std::size_t` required as parameters.
    int
    operator"" _int(const char *str, std::size_t) {
  return std::stoi(str);
}

"123"_int; // == 123, with type `int`
```