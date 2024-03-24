#include "config.h"

/*readline函数实现*/
ssize_t readline(int fd, char *vptr, size_t maxLen) {
  ssize_t n, rc;
  char c, *ptr;

  ptr = vptr;
  for (n = 1; n < maxLen; n++) {
    if ((rc = read(fd, &c, 1)) == 1) {
      *ptr++ = c;
      if (c == '\n')
        break; /* newline is stored, like fgets() */
    } else if (rc == 0) {
      *ptr = 0;
      return (n - 1); /* EOF, n - 1 bytes were read */
    } else
      return (-1); /* error, errno set by read() */
  }

  *ptr = 0; /* null terminate like fgets() */
  return (n);
}

int main(int argc, char **argv) {
  /*声明套接字和链接服务器地址*/
  int sockfd;
  struct sockaddr_in servAddr;

  /*判断是否为合法输入*/
  if (argc != 2) {
    perror("usage:tcpClt <IPaddress>");
    exit(1);
  } // if

  /*(1) 创建套接字*/
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(1);
  } // if

  /*(2) 设置链接服务器地址结构*/
  bzero(&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(PORT);
  
  if (inet_pton(AF_INET, argv[1], &servAddr.sin_addr) < 0) {
    printf("inet_pton error for %s\n", argv[1]);
    exit(1);
  } // if

  /*(3) 发送链接服务器请求*/
  if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("connect error");
    exit(1);
  } // if

  /*(4) 消息处理*/
  char sendLine[MAX_LINE];
  char recvLine[MAX_LINE];

  while (fgets(sendLine, MAX_LINE, stdin) != NULL) {
    write(sockfd, sendLine, strlen(sendLine));

    if (readline(sockfd, recvLine, MAX_LINE) == 0) {
      perror("server terminated prematurely");
      exit(1);
    } // if

    if (fputs(recvLine, stdout) == EOF) {
      perror("fputs error");
      exit(1);
    } // if
  }   // while

  /*(5) 关闭套接字*/
  close(sockfd);
}
