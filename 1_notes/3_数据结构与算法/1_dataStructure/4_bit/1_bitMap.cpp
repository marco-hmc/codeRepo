#include <cstring>
#include <iostream>


class BitMap {
private:
  char *data;
  int size;

public:
  BitMap(int size) {
    this->size = size;
    int dataSize = (size + 7) / 8;
    data = new char[dataSize];
    memset(data, 0, dataSize);
  }

  ~BitMap() { delete[] data; }

  void set(int index) {
    if (index < 0 || index >= size) {
      std::cout << "Invalid index" << std::endl;
      return;
    }

    int byteIndex = index / 8;
    int bitIndex = index % 8;
    data[byteIndex] |= (1 << bitIndex);
  }

  void clear(int index) {
    if (index < 0 || index >= size) {
      std::cout << "Invalid index" << std::endl;
      return;
    }

    int byteIndex = index / 8;
    int bitIndex = index % 8;
    data[byteIndex] &= ~(1 << bitIndex);
  }

  bool get(int index) {
    if (index < 0 || index >= size) {
      std::cout << "Invalid index" << std::endl;
      return false;
    }

    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return (data[byteIndex] & (1 << bitIndex)) != 0;
  }
};

int main() {
  BitMap bitmap(100);
  bitmap.set(5);
  bitmap.set(10);
  bitmap.set(20);

  std::cout << "Bit at index 5: " << bitmap.get(5) << std::endl;
  std::cout << "Bit at index 10: " << bitmap.get(10) << std::endl;
  std::cout << "Bit at index 20: " << bitmap.get(20) << std::endl;

  bitmap.clear(10);

  std::cout << "Bit at index 10 after clearing: " << bitmap.get(10)
            << std::endl;

  return 0;
}