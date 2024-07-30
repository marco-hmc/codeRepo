#include <iostream>
#include <sstream> // 用于std::istringstream的示例

int main() {
  std::istringstream iss("Hello, World!\nThis is a test string.\n1234567890");

  // get 示例
  char ch = iss.get(); // 读取一个字符
  std::cout << "get: " << ch << std::endl;

  // peek 示例
  char peek_ch = iss.peek(); // 预览下一个字符但不移动光标
  std::cout << "peek: " << peek_ch << std::endl;

  // unget 示例
  iss.unget();               // 将光标向前移动一个字符
  char unget_ch = iss.get(); // 再次读取字符
  std::cout << "unget: " << unget_ch << std::endl;

  // putback 示例
  iss.putback('X');            // 将字符'X'放回流中
  char putback_ch = iss.get(); // 读取字符
  std::cout << "putback: " << putback_ch << std::endl;

  // getline 示例
  std::string line;
  std::getline(iss, line); // 读取一行
  std::cout << "getline: " << line << std::endl;

  // ignore 示例
  iss.ignore(5, '\n');     // 忽略5个字符或直到遇到'\n'
  std::getline(iss, line); // 再次读取一行
  std::cout << "ignore: " << line << std::endl;

  // read 示例
  char buffer[6];
  iss.read(buffer, 5); // 读取5个字符
  buffer[5] = '\0';    // 添加字符串结束符
  std::cout << "read: " << buffer << std::endl;

  // readsome 示例
  // readsome的行为在不同情况下可能有所不同，这里仅作为示例
  char readsome_buffer[11];
  std::streamsize n = iss.readsome(readsome_buffer, 10); // 尝试读取10个字符
  readsome_buffer[n] = '\0'; // 添加字符串结束符
  std::cout << "readsome: " << readsome_buffer << std::endl;

  // tellg 示例
  std::streampos position = iss.tellg(); // 获取当前位置
  std::cout << "tellg: " << position << std::endl;

  // seekg 示例
  iss.seekg(0, iss.beg);   // 将光标移动到流的开始
  std::getline(iss, line); // 读取一行
  std::cout << "seekg: " << line << std::endl;

  // seekp 示例
  iss.seekp(5, iss.cur); // 将光标向前移动5个字符
  iss << "C++";          // 在当前位置插入字符串"C++"
  std::cout << "seekp: " << iss.str() << std::endl;
  return 0;
}