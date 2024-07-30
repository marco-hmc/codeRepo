#include <iostream>

class IntWrapper {
public:
  IntWrapper(int value = 0) : m_value(value) {}

  void add(int value) { m_value += value; }

  void subtract(int value) { m_value -= value; }

  int getValue() const { return m_value; }

private:
  int m_value;
};

int main() {
  IntWrapper myNumber(10);
  myNumber.add(5);
  myNumber.subtract(3);
  std::cout << "The value is: " << myNumber.getValue() << std::endl;
  return 0;
}
