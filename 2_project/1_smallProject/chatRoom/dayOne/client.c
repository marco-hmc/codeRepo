#include <netdb.h>
#include <netinet/in.h> //定义数据结构sockaddr_in
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //定义socket函数以及数据结构
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("wrong usage");
    printf("%s host port name\n", argv[0]);
    exit(1);
  }

  struct hostent *host = gethostbyname(argv[1]);
  int clientFd;
  if ((clientFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("fail to create socket");
    exit(1);
  }

  struct sockaddr_in clientAddr;
  bzero(&clientAddr, sizeof(clientAddr));
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = htons((uint16_t)atoi(argv[2]));
  clientAddr.sin_addr = *((struct in_addr *)host->h_addr);

  if (connect(clientFd, (struct sockaddr *)&clientAddr,
              sizeof(struct sockaddr)) == -1) {
    perror("fail to connect");
    exit(1);
  }

  char *buf, *buf_read;
  buf = (char *)malloc(120);
  memset(buf, 0, 120);
  buf_read = (char *)malloc(100);

  if (recv(clientFd, buf, 100, 0) == -1) {
    perror("fail to recv");
    exit(1);
  }
  printf("\n%s\n", buf);
  pid_t pid = fork();

  int sendBytes, recvBytes;
  while (1) {
    if (pid > 0) {
      // 父进程发送消息
      strcpy(buf, argv[3]);
      strcat(buf, ":");
      memset(buf_read, 0, 100);
      fgets(buf_read, 100, stdin);
      strcat(buf_read, "  ");
      strncat(buf, buf_read, strlen(buf_read) - 1);
      if ((sendBytes = send(clientFd, buf, strlen(buf), 0)) == -1) {
        perror("fail to send");
        exit(1);
      }
    } else if (pid == 0) {
      // 子进程接受消息
      memset(buf, 0, 100);
      if (recv(clientFd, buf, 100, 0) <= 0) {
        perror("fail to recv");
        close(clientFd);
        raise(SIGSTOP);
        exit(1);
      }
      printf("%s\n", buf);
    } else
      perror("fork error");
  }

  close(clientFd);
  return 0;
}