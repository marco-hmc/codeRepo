#include <iostream>
#include <regex>
#include <string>

std::string filterChinesePunctuation(const std::string &str) {
  std::regex chinese_punctuation("[\u3000-\u303F]|[\uFF00-\uFFEF]");
  return std::regex_replace(str, chinese_punctuation, "");
}

int main() {
  std::string str = "Hello, World!../';，。？！【】";
  std::string punctuation_filtered = filterChinesePunctuation(str);
  std::cout << "Filtered string: " << punctuation_filtered << std::endl;
  return 0;
}