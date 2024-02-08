#include <algorithm>
#include <cstdlib> // Add the missing include directive for the strverscmp function
#include <ctype.h>
#include <cwctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <stdint.h>
#include <string.h>
#include <vector>

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

int __strverscmp(const wchar_t *p1, const wchar_t *p2) {
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
}

int myStrverscmp(const std::wstring &s1, const std::wstring &s2) {
  return __strverscmp(s1.c_str(), s2.c_str());
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
  std::cout << "before sort" << std::endl;
  for (const auto &filename : filenames) {
    std::wcout << filename << std::endl;
    outputFile << filename << std::endl;
  }
  std::cout << "------------" << std::endl;
  std::cout << "after sort" << std::endl;
  std::sort(filenames.begin(), filenames.end(),
            [](auto a, auto b) { return myStrverscmp(a, b) < 0; });
  for (const auto &filename : filenames) {
    std::wcout << filename << std::endl;
    outputFile << filename << std::endl;
  }
  std::cout << "------------" << std::endl;
  return 0;
}