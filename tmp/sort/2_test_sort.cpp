// #define WIN
#include <iostream>
#ifdef WIN
#pragma comment(lib, "shlwapi.lib")
#include <Shlwapi.h>
#endif

#include <algorithm>
#include <cwctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <stdint.h>
#include <string>
#include <typeinfo>
#include <vector>

namespace {
bool isChinese(char ch) {
  return (ch >= 0x4E00 && ch <= 0x9FFF) || (ch >= 0x3400 && ch <= 0x4DBF) ||
         (ch >= 0xF900 && ch <= 0xFAFF);
}
} // namespace
int __strverscmp(const char *p1, const char *p2) {
/* states: S_N: normal, S_I: comparing integral part, S_F: comparing
           fractionnal parts, S_Z: idem but with leading Zeroes only */
#define S_N 0x0
#define S_I 0x3
#define S_F 0x6
#define S_Z 0x9

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#define CMP 2
#define LEN 3

  /* Compare S1 and S2 as strings holding indices/version numbers,
     returning less than, equal to or greater than zero if S1 is less than,
     equal to or greater than S2 (for more info, see the texinfo doc).
  */

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  static const uint8_t next_state[] = {/* state    x    d    0  */
                                       /* S_N */ S_N, S_I, S_Z,
                                       /* S_I */ S_N, S_I, S_I,
                                       /* S_F */ S_N, S_F, S_F,
                                       /* S_Z */ S_N, S_F, S_Z};

  static const int8_t result_type[] = {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */ CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */ CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */ CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */ CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP};

  if (p1 == p2)
    return 0;

  char c1 = *p1++;
  char c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  int state = S_N + ((c1 == L'0') + (std::isdigit(c1) != 0));

  int diff;
  while ((diff = c1 - c2) == 0) {
    if (c1 == L'\0')
      return diff;
    state = next_state[state];
    c1 = *p1++;
    c2 = *p2++;
    state += (c1 == L'0') + (std::isdigit(c1) != 0); // 是数字就+1,是零就+2
  }

  state = result_type[state * 3 + (((c2 == '0') + (std::isdigit(c2) != 0)))];

  switch (state) {
  case CMP:
    return diff;

  case LEN:
    while (std::isdigit(*p1++))
      if (!std::isdigit(*p2++))
        return 1;

    return std::isdigit(*p2) ? -1 : diff;

  default:
    return state;
  }
} // namespace

int stringCompare(const std::string &str1, const std::string &str2) {
#ifdef WIN
  return StrCmpLogicalW(str1.c_str(), str2.c_str());
#endif

  const char *p1 = str1.c_str();
  char c1 = *p1++;

  const char *p2 = str2.c_str();
  char c2 = *p2++;

  int diff;
  while ((diff = c1 - c2) == 0) {
    if (c1 == L'\0')
      return diff;
    if (isChinese(c1) || isChinese(c2)) {
      const std::locale &loc = std::locale();
      const std::collate<char> &myCollate = std::use_facet<std::collate<char>>(
          loc); // Use std::collate<wchar_t> explicitly
      return myCollate.compare(str1.c_str(), str1.c_str() + str1.length(),
                               str2.c_str(), str2.c_str() + str2.length());
    }
    c1 = *p1++;
    c2 = *p2++;
  }
  return __strverscmp(p1, p2);
}

int main() {
  std::vector<std::string> filenames = {
      "(",   "(1)", "(5",  "(10",  "(10)", "(10.)", "(10.0)", "A",
      "a",   "A1",  "A10", "B",    "b",    "b_",    "b_99",   "01",
      "001", "0.1", "0.5", "0.10", "啊",   "吧",    "一"};
  // 中文
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(filenames.begin(), filenames.end(), g);

  std::ofstream outputFile("output.txt");
  outputFile.clear();
  std::wcout << "before sort" << std::endl;
  for (const auto &filename : filenames) {
    std::cout << filename << std::endl;
    outputFile << filename << std::endl;
  }
  std::cout << "------------" << std::endl;
  std::cout << "after sort" << std::endl;
  std::sort(filenames.begin(), filenames.end(),
            [](auto a, auto b) { return stringCompare(a, b) < 0; });
  for (const auto &filename : filenames) {
    std::cout << filename << std::endl;
    outputFile << filename << std::endl;
  }
  std::wcout << "------------" << std::endl;
  return 0;
}