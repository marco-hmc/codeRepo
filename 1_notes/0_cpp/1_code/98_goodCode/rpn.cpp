#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stack>
#include <stdexcept>

using namespace std;

template <typename IT> double evaluate_rpn(IT it, IT end) {
  stack<double> val_stack;
  auto pop_stack([&]() {
    auto r(val_stack.top());
    val_stack.pop();
    return r;
  });

  map<string, double (*)(double, double)> ops{
      {"+", [](double a, double b) { return a + b; }},
      {"-", [](double a, double b) { return a - b; }},
      {"*", [](double a, double b) { return a * b; }},
      {"/", [](double a, double b) { return a / b; }},
      {"^", [](double a, double b) { return pow(a, b); }},
      {"%", [](double a, double b) { return fmod(a, b); }},
  };

  for (; it != end; ++it) {
    stringstream ss{*it};
    if (double val; ss >> val) {
      val_stack.push(val);
    } else {
      const auto r{pop_stack()};
      const auto l{pop_stack()};
      try {
        const auto &op(ops.at(*it));
        const double result{op(l, r)};
        val_stack.push(result);
      } catch (const out_of_range &) {
        throw invalid_argument(*it);
      }
    }
  }

  return val_stack.top();
}

int main() {
  try {
    cout << evaluate_rpn(istream_iterator<string>{cin}, {}) << '\n';
  } catch (const invalid_argument &e) {
    cout << "Invalid operator: " << e.what() << '\n';
  }
}