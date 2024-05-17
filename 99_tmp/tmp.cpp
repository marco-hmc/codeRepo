#include <iostream>
using namespace std;

int main() {
  char hello[] = "你好你好你好";
  // 输出19,如果你好是通过utf8输入,如果你好是通过gbk输入的,输出13
  std::cout << sizeof(hello) << std::endl;
  std::cout << hello << std::endl; // 输出hello你好

  wchar_t hello_w[] = L"你好你好你好";
  std::cout << sizeof(hello_w)
            << std::endl; // 输出14, utf16编码,尽管"你好"输入是以utf8输入的

  return 0;
}