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
  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 绑定socket到端口
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in address {};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 监听端口
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // 接受客户端连接
  int addrlen = sizeof(address);
  int new_socket;
  if ((new_socket =
           accept(server_fd, reinterpret_cast<struct sockaddr *>(&address),
                  reinterpret_cast<socklen_t *>(&addrlen))) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // 读取客户端发送的数据
  char buffer[BUFFER_SIZE] = {0};
  read(new_socket, buffer, BUFFER_SIZE);
  std::cout << "Message from client: " << buffer << '\n';

  // 发送响应给客户端
  const char *response = "Hello from server";
  send(new_socket, response, strlen(response), 0);
  std::cout << "Response sent to client" << '\n';

  // 关闭socket
  close(new_socket);
  close(server_fd);

  return 0;
}