#include <iostream>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    std::cerr << "Fork failed" << std::endl;
    return 1;
  }

  if (pid == 0) {
    std::cout << "This is the child process. PID: " << getpid() << std::endl;
  } else {
    std::cout << "This is the parent process. Child PID: " << pid << std::endl;
  }

  return 0;
}