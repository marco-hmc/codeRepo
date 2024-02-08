// #include <algorithm>
// #include <fstream>
// #include <iostream>
// #include <random>
// #include <vector>

// int main() {
//   std::locale::global(std::locale(""));

//   std::vector<std::wstring> filenames = {
//       L"(",   L"(1)", L"(5",  L"(10",  L"(10)", L"(10.)", L"(10.0)", L"A",
//       L"a",   L"A1",  L"A10", L"B",    L"b",    L"b_",    L"b_99",   L"01",
//       L"001", L"0.1", L"0.5", L"0.10", L"啊",   L"吧",    L"一"};
//   std::random_device rd;
//   std::mt19937 g(rd());
//   std::shuffle(filenames.begin(), filenames.end(), g);

//   std::wofstream outputFile("output.txt");
//   outputFile.imbue(std::locale(""));
//   outputFile.clear();
//   std::sort(filenames.begin(), filenames.end());
//   for (const auto &filename : filenames) {
//     std::wcout << filename << std::endl;
//     outputFile << filename << std::endl;
//   }
//   std::cout << "--------done---------" << std::endl;
//   return 0;
// }
#include <fstream>
#include <io.h>
#include <iostream>
#include <locale>

int main() {
  // 设置全局区域设置为用户的默认区域设置
  // std::locale::global(std::locale(""));

  // // 创建一个宽字符输出文件流,并设置其区域设置
  // std::wofstream outputFile("output.txt");
  // outputFile.imbue(std::locale(""));
  // outputFile.clear(); // 清除文件内容

  // // 创建一个宽字符字符串
  std::wstring str = L"你好";

  // // 将宽字符字符串输出到控制台
  // std::wcout << str << std::endl;

  // // 将宽字符字符串输出到文件
  // outputFile << str << std::endl;
  // std::wcout.imbue(std::locale(""));
  _setmode(_fileno(stdout), _O_WTEXT);

  std::wcout << str << std::endl;
  std::wcout << L"hi" << std::endl;
  std::cout << "all the money go to my pocket" << std::endl;

  return 0;
}
