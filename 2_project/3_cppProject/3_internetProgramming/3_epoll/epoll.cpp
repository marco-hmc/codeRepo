#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10

int main() {
  int server_fd, client_fd, epoll_fd;
  struct sockaddr_in address;
  char buffer[BUFFER_SIZE];
  int addrlen = sizeof(address);

  // 创建epoll实例
  epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }

  // 创建服务器socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // 设置服务器socket为非阻塞模式
  int flags = fcntl(server_fd, F_GETFL, 0);
  fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

  // 设置服务器地址和端口
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 绑定socket到端口
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // 监听端口
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // 创建epoll事件结构体
  struct epoll_event event;
  event.events = EPOLLIN | EPOLLET; // 监听读事件并设置边缘触发模式
  event.data.fd = server_fd;

  // 将服务器socket添加到epoll实例中
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
    perror("epoll_ctl");
    exit(EXIT_FAILURE);
  }

  // 创建用于存储事件的数组
  struct epoll_event events[MAX_EVENTS];

  while (true) {
    // 等待事件发生
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    if (num_events == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }

    // 处理每个事件
    for (int i = 0; i < num_events; i++) {
      if (events[i].data.fd == server_fd) {
        // 处理新的客户端连接
        while (true) {
          client_fd = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen);
          if (client_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
              // 已经处理完所有的连接
              break;
            } else {
              perror("accept");
              exit(EXIT_FAILURE);
            }
          }

          // 设置客户端socket为非阻塞模式
          flags = fcntl(client_fd, F_GETFL, 0);
          fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);

          // 将新的客户端socket添加到epoll实例中
          event.events = EPOLLIN | EPOLLET;
          event.data.fd = client_fd;
          if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1) {
            perror("epoll_ctl");
            exit(EXIT_FAILURE);
          }

          std::cout << "New connection, socket fd is " << client_fd
                    << std::endl;
        }
      } else {
        // 处理客户端发送的数据
        while (true) {
          int valread = read(events[i].data.fd, buffer, BUFFER_SIZE);
          if (valread == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
              // 已经读取完所有的数据
              break;
            } else {
              perror("read");
              close(events[i].data.fd);
              break;
            }
          } else if (valread == 0) {
            // 客户端断开连接
            close(events[i].data.fd);
            std::cout << "Client disconnected, socket fd is "
                      << events[i].data.fd << std::endl;
            break;
          } else {
            // 处理客户端发送的数据
            buffer[valread] = '\0';
            std::cout << "Received message: " << buffer << std::endl;
          }
        }
      }
    }
  }

  close(server_fd);
  close(epoll_fd);

  return 0;
}