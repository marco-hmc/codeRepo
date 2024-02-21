#include <iostream>

enum class RangeBoundedType {
  kBounded,
  kUnBounded,
  kPositiveInfinite,
  kNegativeInfinite,
};

class BmRange {
public:
  struct BmRangeValue {
    double value;
    RangeBoundedType boundedType;

    bool operator<(const BmRangeValue &other) const {
      auto isNegInf = [](const BmRangeValue &value) {
        return value.boundedType == RangeBoundedType::kNegativeInfinite;
      };

      if (isNegInf(*this)) {
        return true; // Both are negative infinite, so they are equal
      } else {
        return false;
      }
    }
  };

private:
  BmRangeValue min;
  BmRangeValue max;
};

int main() {
  int num;
  std::cout << "hello world: ";
  return 0;
}