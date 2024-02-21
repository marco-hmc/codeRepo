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
bool isChinese(wchar_t ch) {
  return (ch >= 0x4E00 && ch <= 0x9FFF) || (ch >= 0x3400 && ch <= 0x4DBF) ||
         (ch >= 0xF900 && ch <= 0xFAFF);
}
} // namespace
int __strverscmp(const wchar_t *p1, const wchar_t *p2) {
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
  int state = S_N + ((c1 == L'0') + (std::iswdigit(c1) != 0));

  int diff;
  while ((diff = c1 - c2) == 0) {
    if (c1 == L'\0')
      return diff;
    state = next_state[state];
    c1 = *p1++;
    c2 = *p2++;
    state += (c1 == L'0') + (std::iswdigit(c1) != 0); // 是数字就+1,是零就+2
  }

  state = result_type[state * 3 + (((c2 == '0') + (std::iswdigit(c2) != 0)))];

  switch (state) {
  case CMP:
    return diff;

  case LEN:
    while (std::iswdigit(*p1++))
      if (!std::iswdigit(*p2++))
        return 1;

    return std::iswdigit(*p2) ? -1 : diff;

  default:
    return state;
  }
} // namespace

int stringCompare(const std::wstring &str1, const std::wstring &str2) {
#ifdef WIN
  return StrCmpLogicalW(str1.c_str(), str2.c_str());
#endif

  const wchar_t *p1 = str1.c_str();
  wchar_t c1 = *p1++;

  const wchar_t *p2 = str2.c_str();
  wchar_t c2 = *p2++;

  int diff;
  while ((diff = c1 - c2) == 0) {
    if (c1 == L'\0')
      return diff;
    if (isChinese(c1) || isChinese(c2)) {
      const std::locale &loc = std::locale();
      const std::collate<wchar_t> &myCollate =
          std::use_facet<std::collate<wchar_t>>(
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
  std::vector<std::wstring> filenames = {
      L"(",   L"(1)", L"(5",  L"(10",  L"(10)", L"(10.)", L"(10.0)", L"A",
      L"a",   L"A1",  L"A10", L"B",    L"b",    L"b_",    L"b_99",   L"01",
      L"001", L"0.1", L"0.5", L"0.10", L"啊",   L"吧",    L"一"};
  // 中文
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(filenames.begin(), filenames.end(), g);

  std::wofstream outputFile("output.txt");
  outputFile.clear();
  std::wcout << "before sort" << std::endl;
  for (const auto &filename : filenames) {
    std::wcout << filename << std::endl;
    outputFile << filename << std::endl;
  }
  std::wcout << "------------" << std::endl;
  std::wcout << "after sort" << std::endl;
  std::sort(filenames.begin(), filenames.end(),
            [](auto a, auto b) { return stringCompare(a, b) < 0; });
  for (const auto &filename : filenames) {
    std::wcout << filename << std::endl;
    outputFile << filename << std::endl;
  }
  std::wcout << "------------" << std::endl;
  return 0;
}