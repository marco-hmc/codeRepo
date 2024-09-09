#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

  // 创建服务器socket
  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 设置服务器地址和端口
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 绑定socket到端口
  if (bind(server_fd, reinterpret_cast<struct sockaddr *>(&address),
           sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 监听端口
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // 设置非阻塞模式
  fcntl(server_fd, F_SETFL, O_NONBLOCK);

  // 初始化文件描述符集合
  fd_set read_fds;
  FD_ZERO(&read_fds);
  FD_SET(server_fd, &read_fds);
  int max_fd = server_fd;

  while (true) {
    fd_set temp_fds = read_fds; // 临时文件描述符集合，用于select调用

    // 使用select监控文件描述符
    int activity = select(max_fd + 1, &temp_fds, nullptr, nullptr, nullptr);
    // 参数1：最大文件描述符+1
    // 参数2：读文件描述符集合，用于监视是否有数据可读
    // 参数3：写文件描述符集合，用于监视是否有数据可写
    // 参数4：异常文件描述符集合，用于监视是否有异常情况
    // 参数5：超时时间，NULL表示无限等待

    if (activity < 0 && errno != EINTR) {
      perror("select error");
    }

    // 检查是否有新的连接
    if (FD_ISSET(server_fd, &temp_fds)) {
      int client_fd;
      if ((client_fd =
               accept(server_fd, reinterpret_cast<struct sockaddr *>(&address),
                      &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
      }

      // 添加新的客户端socket到文件描述符集合
      FD_SET(client_fd, &read_fds);
      if (client_fd > max_fd) {
        max_fd = client_fd;
      }

      std::cout << "New connection, socket fd is " << client_fd << '\n';
    }

    // 检查现有连接是否有数据可读
    char buffer[BUFFER_SIZE];
    for (int i = 0; i <= max_fd; i++) {
      if (FD_ISSET(i, &temp_fds)) {
        if (i == server_fd) {
          continue;
        }

        ssize_t valread = read(i, buffer, BUFFER_SIZE);
        if (valread == 0) {
          // 客户端断开连接
          close(i);
          FD_CLR(i, &read_fds);
          std::cout << "Client disconnected, socket fd is " << i << '\n';
        } else {
          // 处理客户端发送的数据
          buffer[valread] = '\0';
          std::cout << "Received message: " << buffer << '\n';
        }
      }
    }
  }

  return 0;
}