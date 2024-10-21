#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int main() {
  int server_fd, client_fd;
  struct sockaddr_in address;
  char buffer[BUFFER_SIZE];
  int addrlen = sizeof(address);

  // 创建服务器socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 设置服务器地址和端口
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 绑定socket到端口
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 监听端口
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // 初始化pollfd结构体数组
  std::vector<pollfd> poll_fds;
  pollfd server_pollfd = {server_fd, POLLIN, 0};
  poll_fds.push_back(server_pollfd);

  while (true) {
    // 调用poll函数监控文件描述符
    int activity = poll(poll_fds.data(), poll_fds.size(), -1);

    if (activity < 0) {
      perror("poll error");
      exit(EXIT_FAILURE);
    }

    // 检查是否有新的连接
    if (poll_fds[0].revents & POLLIN) {
      if ((client_fd = accept(server_fd, (struct sockaddr *)&address,
                              (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
      }

      // 添加新的客户端socket到pollfd数组
      pollfd client_pollfd = {client_fd, POLLIN, 0};
      poll_fds.push_back(client_pollfd);

      std::cout << "New connection, socket fd is " << client_fd << std::endl;
    }

    // 检查现有连接是否有数据可读
    for (size_t i = 1; i < poll_fds.size(); i++) {
      if (poll_fds[i].revents & POLLIN) {
        int valread = read(poll_fds[i].fd, buffer, BUFFER_SIZE);
        if (valread == 0) {
          // 客户端断开连接
          close(poll_fds[i].fd);
          poll_fds.erase(poll_fds.begin() + i);
          std::cout << "Client disconnected, socket fd is " << poll_fds[i].fd
                    << std::endl;
          i--; // 调整索引以处理已删除的元素
        } else {
          // 处理客户端发送的数据
          buffer[valread] = '\0';
          std::cout << "Received message: " << buffer << std::endl;
        }
      }
    }
  }

  return 0;
}