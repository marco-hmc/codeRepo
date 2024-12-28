#pragma once

class coonnectionPool {
public:
  coonnectionPool() {}
  ~coonnectionPool() = default;

  coonnectionPool(const coonnectionPool &) = default;
  coonnectionPool &operator=(const coonnectionPool &) = default;
  coonnectionPool(coonnectionPool &&) = default;
  coonnectionPool &operator=(coonnectionPool &&) = default;

  void myFunction();
};