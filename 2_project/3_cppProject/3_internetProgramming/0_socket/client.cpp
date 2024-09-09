#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

  // 创建socket文件描述符
  int sock = 0;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  struct sockaddr_in serv_addr {};
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  // 将地址转换为二进制形式
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported" << '\n';
    return -1;
  }

  // 连接服务器
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection Failed" << '\n';
    return -1;
  }

  // 发送数据到服务器
  const char *message = "Hello from client";
  send(sock, message, strlen(message), 0);
  std::cout << "Message sent to server" << '\n';

  // 读取服务器响应
  char buffer[BUFFER_SIZE] = {0};
  read(sock, buffer, BUFFER_SIZE);
  std::cout << "Message from server: " << buffer << '\n';

  // 关闭socket
  close(sock);

  return 0;
}