#include <arpa/inet.h>
#include <cstdio>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

void errif(bool, const char *);

#define BUFFER_SIZE 1024
int main() {
  int clntFd = socket(AF_INET, SOCK_STREAM, 0);
  errif(clntFd == -1, "socket create error");

  struct sockaddr_in serv_addr;
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(8888);
  errif(connect(clntFd, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1,
        "connect error");

  while (true) {
    char buf[BUFFER_SIZE];
    bzero(&buf, sizeof(buf));
    scanf("%s", buf);

    ssize_t write_bytes = write(clntFd, buf, sizeof(buf));
    errif(write_bytes == -1, "socket already disconnected");

    bzero(&buf, sizeof(buf));
    ssize_t read_bytes = read(clntFd, buf, sizeof(buf));
    if (read_bytes > 0) {
      printf("receive from server: %s\n", buf);
    } else {
      printf("socket already disconnected\n");
      break;
    }
  }
  close(clntFd);
  return 0;
}