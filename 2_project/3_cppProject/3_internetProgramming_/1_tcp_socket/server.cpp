#include "config.h"

/*声明缓冲区*/
char buf[MAX_LINE];

int main(int argc, char **argv) {
  /*(1) 初始化监听套接字listenFd*/
  int listenFd;
  if ((listenFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket error");
    exit(1);
  }

  /*(2) 设置服务器sockaddr_in结构*/
  /*声明服务器地址和客户链接地址*/
  struct sockaddr_in servAddr;
  bzero(&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //表明可接受任意IP地址
  servAddr.sin_port = htons(PORT);

  /*(3) 绑定套接字和端口*/
  if (bind(listenFd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("bind error");
    exit(1);
  } // if

  /*(4) 监听客户请求*/
  if (listen(listenFd, LISTENQ) < 0) {
    perror("listen error");
    exit(1);
  } // if

  /*(5) 接受客户请求*/
  int connFd;
  pid_t childPid;
  struct sockaddr_in cliAddr;
  while (true) {
    socklen_t cliLen = sizeof(cliAddr);
    if ((connFd = accept(listenFd, (struct sockaddr *)&cliAddr, &cliLen)) < 0) {
      perror("accept error");
      exit(1);
    } // if

    //新建子进程单独处理链接
    if ((childPid = fork()) == 0) {
      close(listenFd);
      // str_echo
      ssize_t n;
      char buff[MAX_LINE];
      while ((n = read(connFd, buff, MAX_LINE)) > 0) {
        write(connFd, buff, n);
      }
      exit(0);
    }
    close(connFd);
  } // for

  /*(6) 关闭监听套接字*/
  close(listenFd);
}
