#include <fstream>
#include <iostream>

int main() {
  std::fstream file;

  file.open("example.txt", std::ios::out | std::ios::app);

  if (file.is_open()) {
    file << "Hello, World!" << std::endl;
    file.close();
  } else {
    std::cout << "无法打开文件！" << std::endl;
  }

  file.open("example.txt", std::ios::in);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
    }

    file.close();
  } else {
    std::cout << "无法打开文件！" << std::endl;
  }

  return 0;
}