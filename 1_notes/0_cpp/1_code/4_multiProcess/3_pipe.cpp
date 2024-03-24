#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
  char write_msg[BUFFER_SIZE] = "Hello, child!";
  char read_msg[BUFFER_SIZE];
  int fd[2];

  // create a pipe
  if (pipe(fd) == -1) {
    std::cerr << "Pipe failed" << std::endl;
    return 1;
  }

  pid_t pid = fork();

  if (pid < 0) { // error occurred
    std::cerr << "Fork Failed" << std::endl;
    return 1;
  } else if (pid > 0) { // parent process
    // close the unused end of the pipe
    close(fd[READ_END]);

    // write to the pipe
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

    // close the write end of the pipe
    close(fd[WRITE_END]);

    // wait for the child process to finish
    wait(NULL);
  } else { // child process
    // close the unused end of the pipe
    close(fd[WRITE_END]);

    // read from the pipe
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    std::cout << "read: " << read_msg << std::endl;

    // close the read end of the pipe
    close(fd[READ_END]);
  }

  return 0;
}