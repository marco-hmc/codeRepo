#include <cassert>
#include <iostream>
#include <string>
#include <vector>

enum class State {
  START,
  DIGIT1,
  DIGIT2,
  DIGIT3,
  DASH,
  DIGIT4,
  DIGIT5,
  DIGIT6,
  DIGIT7,
  DASH2,
  DIGIT8,
  DIGIT9,
  DIGIT10,
  DIGIT11,
  END
};

bool validatePhoneNumber(const std::string &phoneNumber) {
  State currentState = State::START;

  for (char c : phoneNumber) {
    switch (currentState) {
    case State::START:
      if (isdigit(c)) {
        currentState = State::DIGIT1;
      } else {
        return false;
      }
      break;
    case State::DIGIT1:
    case State::DIGIT2:
    case State::DIGIT3:
      if (isdigit(c)) {
        currentState = static_cast<State>(static_cast<int>(currentState) + 1);
      } else if (c == '-' && currentState == State::DIGIT3) {
        currentState = State::DASH;
      } else {
        return false;
      }
      break;
    case State::DASH:
      if (isdigit(c)) {
        currentState = State::DIGIT4;
      } else {
        return false;
      }
      break;
    case State::DIGIT4:
    case State::DIGIT5:
    case State::DIGIT6:
    case State::DIGIT7:
      if (isdigit(c)) {
        currentState = static_cast<State>(static_cast<int>(currentState) + 1);
      } else if (c == '-' && currentState == State::DIGIT7) {
        currentState = State::DASH2;
      } else {
        return false;
      }
      break;
    case State::DASH2:
      if (isdigit(c)) {
        currentState = State::DIGIT8;
      } else {
        return false;
      }
      break;
    case State::DIGIT8:
    case State::DIGIT9:
    case State::DIGIT10:
    case State::DIGIT11:
      if (isdigit(c)) {
        currentState = static_cast<State>(static_cast<int>(currentState) + 1);
      } else {
        return false;
      }
      break;
    case State::END:
      return false;
    }
  }

  return currentState == State::DIGIT11;
}

int main() {
  std::vector<std::string> testCases = {
      "123-4567-4567",  // 正确的电话号码格式
      "123-456-4567",   // 缺少一位数字
      "123-4567-456",   // 缺少一位数字
      "123-4567-45678", // 多一位数字
      "123-4567-4567a", // 包含非数字字符
      "12345674567",    // 缺少分隔符
      "123-4567--4567", // 多一个分隔符
      "-123-4567-4567", // 开头有分隔符
      "123-4567-4567-"  // 结尾有分隔符
  };

  assert(validatePhoneNumber(testCases[0]) == true);
  for (int i = 1; i < testCases.size(); ++i) {
    assert(validatePhoneNumber(testCases[i]) == false);
  }

  return 0;
}