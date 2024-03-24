#include <iostream>
#include <sys/types.h>
#include <sys/wait.h> // Add the missing include statement
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    std::cerr << "Fork failed" << std::endl;
    return 1;
  }

  if (pid == 0) { // This block will be executed in the child process
    char *args[] = {(char *)"/bin/ls", (char *)"-l", NULL};
    execvp(args[0], args);                   // Executes the ls command
    std::cerr << "Exec failed" << std::endl; // Only gets here if exec failed
    return 1;
  } else { // This block will be executed in the parent process
    int status;
    waitpid(pid, &status, 0); // Wait for the child process to finish
    std::cout << "Child finished with status " << status << std::endl;
  }

  return 0;
}