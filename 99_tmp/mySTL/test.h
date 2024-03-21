#include <vector>

#include "Lib/redbud/io/color.h"

namespace test {

#define green redbud::io::state::manual << redbud::io::hfg::green
#define red redbud::io::state::manual << redbud::io::hfg::red

class TestCase {
public:
  TestCase(const char *case_name) : case_name_(case_name){};
  virtual void Run() = 0;

public:
  const char *case_name_;
  bool nTestResult;
  unsigned int nFailed;
  unsigned int nPassed;
};

///////////////////////////////////////////////////
class UnitTest {
  static UnitTest *GetInstance();
  TestCase *RegisterTestCase(TestCase *test_case);
  void Run();

public:
  TestCase *CurrentTestCase;
  unsigned int nFailed;
  unsigned int nPassed;

protected:
  std::vector<TestCase *> test_cases_;
};
///////////////////////////////////////////////////

UnitTest *UnitTest::GetInstance() {
  static UnitTest instance;
  return &instance;
};

TestCase *UnitTest::RegisterTestCase(TestCase *test_case) {
  test_cases_.push_back(test_case);
  return test_case;
};

void UnitTest::Run() {
  for (auto &test_case : test_cases_) {
    CurrentTestCase = test_case;
    CurrentTestCase->nTestResult = true;
    CurrentTestCase->nFailed = 0;
    CurrentTestCase->nPassed = 0;
    std::cout << green << "============================================\n";
    std::cout << green << "Running test case: " << CurrentTestCase->case_name_
              << std::endl;
    CurrentTestCase->Run();
    if (CurrentTestCase->nFailed == 0)
      std::cout << green << "Test case passed\n";
    else
      std::cout << red << "Test case failed\n";

    std::cout << " " << CurrentTestCase->nPassed << " / "
              << CurrentTestCase->nFailed + CurrentTestCase->nPassed
              << " Cases passed. ( "
              << CurrentTestCase->nPassed /
                     (CurrentTestCase->nFailed + CurrentTestCase->nPassed) * 100
              << "% )\n";

    if (CurrentTestCase->nTestResult)
      ++nPassed;
    else
      ++nFailed;
  }
  std::cout << green << "============================================\n";
  std::cout << green << " Total TestCase : " << nPassed + nFailed << "\n";
  std::cout << green << " Total Passed : " << nPassed << "\n";
  std::cout << red << " Total Failed : " << nFailed << "\n";
  std::cout << green << " " << nPassed << " / " << nFailed + nPassed
            << " TestCases passed. ( " << nPassed / (nFailed + nPassed) * 100
            << "% )\n";
};
///////////////////////////////////////////////////
#define EXPECT_TRUE(Condition)                                                 \
  do {                                                                         \
    if (Condition) {                                                           \
      std::cout << green << "  [PASS] " << #Condition << "\n";                 \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #Condition << "\n";                   \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_FALSE(Condition)                                                \
  do {                                                                         \
    if (!Condition) {                                                          \
      std::cout << green << "  [PASS] " << #Condition << "\n";                 \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #Condition << "\n";                   \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)
///////////////////////////////////////////////////

#define EXPECT_EQ(v1, v2)                                                      \
  do {                                                                         \
    if (v1 == v2) {                                                            \
      std::cout << green << "  [PASS] " << #v1 << " == " << #v2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #v1 << " == " << #v2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_NE(v1, v2)                                                      \
  do {                                                                         \
    if (v1 != v2) {                                                            \
      std::cout << green << "  [PASS] " << #v1 << " != " << #v2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #v1 << " != " << #v2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_LT(v1, v2)                                                      \
  do {                                                                         \
    if (v1 < v2) {                                                             \
      std::cout << green << "  [PASS] " << #v1 << " < " << #v2 << "\n";        \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #v1 << " < " << #v2 << "\n";          \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_LE(v1, v2)                                                      \
  do {                                                                         \
    if (v1 <= v2) {                                                            \
      std::cout << green << "  [PASS] " << #v1 << " <= " << #v2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #v1 << " <= " << #v2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_GT(v1, v2)                                                      \
  do {                                                                         \
    if (v1 > v2) {                                                             \
      std::cout << green << "  [PASS] " << #v1 << " > " << #v2 << "\n";        \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #v1 << " > " << #v2 << "\n";          \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_GE(v1, v2)                                                      \
  do {                                                                         \
    if (v1 >= v2) {                                                            \
      std::cout << green << "  [PASS] " << #v1 << " >= " << #v2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #v1 << " >= " << #v2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

///////////////////////////////////////////////////

#define EXPECT_STREQ(s1, s2)                                                   \
  do {                                                                         \
    if (!s1 || !s2) {                                                          \
      if (!s1 && !s2) {                                                        \
        std::cout << green << "  [PASS] " << #s1 << " == " << #s2 << "\n";     \
        CurrentTestCase->nPassed++;                                            \
      } else {                                                                 \
        std::cout << red << "  [FAIL] " << #s1 << " == " << #s2 << "\n";       \
        CurrentTestCase->nFailed++;                                            \
        CurrentTestCase->nTestResult = false;                                  \
      }                                                                        \
    } else if (strcmp(s1, s2) == 0) {                                          \
      std::cout << green << "  [PASS] " << #s1 << " == " << #s2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #s1 << " == " << #s2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  }

#define EXPECT_STRNE(s1, s2)                                                   \
  do {                                                                         \
    if (!s1 || !s2) {                                                          \
      if (s1 || s2) {                                                          \
        std::cout << green << "  [PASS] " << #s1 << " != " << #s2 << "\n";     \
        CurrentTestCase->nPassed++;                                            \
      } else {                                                                 \
        std::cout << red << "  [FAIL] " << #s1 << " != " << #s2 << "\n";       \
        CurrentTestCase->nFailed++;                                            \
        CurrentTestCase->nTestResult = false;                                  \
      }                                                                        \
    } else if (strcmp(s1, s2) != 0) {                                          \
      std::cout << green << "  [PASS] " << #s1 << " != " << #s2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #s1 << " != " << #s2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  }
///////////////////////////////////////////////////

#define EXPECT_PTR_EQ(p1, p2)                                                  \
  do {                                                                         \
    if (*p1 == *p2) {                                                          \
      std::cout << green << "  [PASS] " << #p1 << " == " << #p2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #p1 << " == " << #p2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_PTR_NE(p1, p2)                                                  \
  do {                                                                         \
    if (*p1 != *p2) {                                                          \
      std::cout << green << "  [PASS] " << #p1 << " != " << #p2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #p1 << " == " << #p2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_PTR_RANGE_EQ(p1, p2, n)                                         \
  do {                                                                         \
    bool is_equal = true;                                                      \
    for (int i = 0; i < n; i++) {                                              \
      if (p1[i] != p2[i]) {                                                    \
        is_equal = false;                                                      \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
    if (is_equal) {                                                            \
      std::cout << green << "  [PASS] " << #p1 << " == " << #p2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #p1 << " == " << #p2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_PTR_RANGE_NE(p1, p2, n)                                         \
  do {                                                                         \
    bool is_equal = true;                                                      \
    for (int i = 0; i < n; i++) {                                              \
      if (p1[i] != p2[i]) {                                                    \
        is_equal = false;                                                      \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
    if (!is_equal) {                                                           \
      std::cout << green << "  [PASS] " << #p1 << " != " << #p2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #p1 << " != " << #p2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

///////////////////////////////////////////////////

#define EXPECT_CONTAINER_EQ(c1, c2)                                            \
  do {                                                                         \
    auto first1 = std::begin(c1), lats1 = std::end(c1);                        \
    auto first2 = std::begin(c2), lats1 = std::end(c2);                        \
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {           \
      if (*first1 != *first2) {                                                \
        break;                                                                 \
        return;                                                                \
      }                                                                        \
    }                                                                          \
    if (first1 == last1 && first2 == last2) {                                  \
      std::cout << green << "  [PASS] " << #c1 << " == " << #c2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #c1 << " == " << #c2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)

#define EXPECT_CONTAINER_NE(c1, c2)                                            \
  do {                                                                         \
    auto first1 = std::begin(c1), lats1 = std::end(c1);                        \
    auto first2 = std::begin(c2), lats1 = std::end(c2);                        \
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {           \
      if (*first1 != *first2) {                                                \
        break;                                                                 \
        return;                                                                \
      }                                                                        \
    }                                                                          \
    if (first1 != last1 || first2 != last2) {                                  \
      std::cout << green << "  [PASS] " << #c1 << " == " << #c2 << "\n";       \
      CurrentTestCase->nPassed++;                                              \
    } else {                                                                   \
      std::cout << red << "  [FAIL] " << #c1 << " == " << #c2 << "\n";         \
      CurrentTestCase->nFailed++;                                              \
      CurrentTestCase->nTestResult = false;                                    \
    }                                                                          \
  } while (0)
///////////////////////////////////////////////////

#if defined(_DEBUG) || defined(DEBUG)
#define LEN1 10000
#define LEN2 100000
#define LEN3 1000000
#else
#define LEN1 100000
#define LEN2 1000000
#define LEN3 10000000
#endif

#define SCALE_LLL(N) (N * 20)
#define SCALE_LL(N) (N * 10)
#define SCALE_L(N) (N * 5)
#define SCALE_M(N) (N)
#define SCALE_S(N) (N / 5)
#define SCALE_SS(N) (N / 10)
#define SCALE_SSS(N) (N / 20)

#define WIDE 14
///////////////////////////////////////////////////
#define PASSED std::cout << "[ PASSED ]\n"

#define COUT(container)                                                        \
  do {                                                                         \
    std::string con_name = #container;                                         \
    std::cout << " " << con_name << " :";                                      \
    for (auto it : container)                                                  \
      std::cout << " " << it;                                                  \
    std::cout << "\n";                                                         \
  } while (0)

#define STR_COUT(str)                                                          \
  do {                                                                         \
    std::string str_name = #str;                                               \
    std::cout << " " << str_name << " : " << str << "\n";                      \
  } while (0)

#define FUN_AFTER(con, fun)                                                    \
  do {                                                                         \
    std::string fun_name = #fun;                                               \
    std::cout << " After " << fun_name << " :\n";                              \
    fun;                                                                       \
    COUT(con);                                                                 \
  } while (0)

#define STR_FUN_AFTER(str, fun)                                                \
  do {                                                                         \
    std::string fun_name = #fun;                                               \
    std::cout << " After " << fun_name << " :\n";                              \
    fun;                                                                       \
    STR_COUT(str);                                                             \
  } while (0)

#define FUN_VALUE(fun)                                                         \
  do {                                                                         \
    std::string fun_name = #fun;                                               \
    std::cout << " " << fun_name << " : " << fun << "\n";                      \
  } while (0)

} // namespace test