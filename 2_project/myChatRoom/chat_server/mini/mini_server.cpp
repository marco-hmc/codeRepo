#include <arpa/inet.h>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <netinet/in.h> // Add this line to include the necessary header file
#include <netinet/in.h> //定义数据结构sockaddr_in
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ipc.h>
#include <sys/shm.h> //共享内存
#include <sys/socket.h>
#include <sys/socket.h> //提供socket函数和数据结构
#include <sys/stat.h>   //文件属性
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h> //数据类型定义
#include <unistd.h>

// 当客户端连接服务端时，向客户端发送此字符串
#define WELCOME "|---------------Welcome to the chat room!----------------|"
#define PERM S_IRUSR | S_IWUSR // 用户读写

class Server {
public:
  Server(int port) : port_(port) { init(); }

  void init() {
    std::cout << "Server initialized" << std::endl;
    createSocket();
    listenPort();
  }

  void createSocket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
      std::cerr << "Failed to create socket" << std::endl;
      return;
    }

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port_);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) ==
        -1) {
      perror("fail to bind");
      exit(1);
    }

    printf("bind success!\n");
    sockFd_ = sockfd;
  }

  // 创建共享存储区
  int shm_create() {
    int shmid;
    if ((shmid = shmget(IPC_PRIVATE, 1024, PERM)) == -1) {
      fprintf(stderr, "Create Share Memory Error:%s\n\a", strerror(errno));
      exit(1);
    }
    return shmid;
  }

  // 得到当前系统的时间
  void get_cur_time(char *time_str) {
    struct timeval now;
    gettimeofday(&now, NULL);
    strcpy(time_str, ctime(&now.tv_sec));
  }

  void listenPort() {
    if (listen(sockFd_, 10) == -1) {
      perror("fail to listen");
      exit(1);
    }
    printf("listen success!\n");
  }

  void Start() {
    std::cout << "Server started on port " << port_ << std::endl;
    while (1) {
      struct sockaddr_in client_addr;
      socklen_t addrlen = sizeof(client_addr);
      int clientFd = accept(sockFd_, (struct sockaddr *)&client_addr, &addrlen);
      if (clientFd == -1) {
        perror("fail to accept");
        exit(1);
      }
      printf("accept success!\n");

      char address[20];
      inet_ntop(AF_INET, &client_addr.sin_addr, address, sizeof(address));
      printf("server: got connection from %s\n", address);

      send(clientFd, WELCOME, strlen(WELCOME), 0); // 发送问候信息
      char *buf = (char *)malloc(255);

      int shmid = shm_create(); // 创建共享存储区

      pid_t ppid = fork();
      if (ppid == 0) // 子进程
      {
        pid_t pid = fork(); // 子进程创建子进程
        while (1) {
          if (pid > 0) {
            // buf = (char *)malloc(255);
            // 父进程用于接收信息
            memset(buf, 0, 255);
            printf("OK\n");
            int recvBytes;
            if ((recvBytes = recv(clientFd, buf, 255, 0)) <= 0) {
              perror("fail to recv");
              close(clientFd);
              raise(SIGKILL);
              exit(1);
            }
            // shmat将shmid所代表的全局的共享存储区关联到本进程的进程空间
            char *write_addr = static_cast<char *>(shmat(shmid, 0, 0));
            memset(write_addr, '\0', 1024);

            // 把接收到的消息存入共享存储区中
            strncpy(write_addr, buf, 1024);

            // 把接收到的消息连接此刻的时间字符串输出到标准输出
            char *time_str;
            get_cur_time(time_str);
            strcat(buf, time_str);
            printf("%s\n", buf);
          } else if (pid == 0) {
            // 子进程的子进程用于发送消息
            sleep(1); // 子进程先等待父进程把接收到的信息存入共享存储区
            char *read_addr;
            // 读取共享存储区的内容
            read_addr = static_cast<char *>(shmat(shmid, 0, 0));

            // temp存储上次读取过的内容,每次先判断是否已经读取过该消息
            char *temp, *time_str;
            if (strcmp(temp, read_addr) != 0) {
              strcpy(temp, read_addr); // 更新temp，表示已经读取过该消息

              get_cur_time(time_str);
              strcat(read_addr, "  ");
              strcat(read_addr, time_str);
              if (send(clientFd, read_addr, strlen(read_addr), 0) == -1) {
                perror("fail to send");
                exit(1);
              }
              memset(read_addr, '\0', 1024);
              strcpy(read_addr, temp);
            }
          } else
            perror("fail to fork");
        }
      }
    }
  }

  void Stop() {
    std::cout << "Server stopped" << std::endl;
    // TODO: Implement server shutdown logic here
  }

private:
  int port_;
  int sockFd_;
};

int main() {
  Server server(8080);
  server.Start();
  server.Stop();

  return 0;
}