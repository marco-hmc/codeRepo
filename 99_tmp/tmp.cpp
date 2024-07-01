#include <iostream>
using namespace std;

class Base_n2 {
public:
  void func(int &n) {
    n = 1; // 或者提供一个默认行为
  }

  virtual ~Base_n2() = default;
};

class A_n2 : public Base_n2 {
public:
  virtual void func(int &n) { n = 2; }
};

class B_n2 : public A_n2 {
public:
  void func(int &n) override { n = 3; }
};

int main() {
  int n = 0;
  Base_n2 *pBase = new B_n2();
  pBase->func(n);
  cout << n << endl;
  return 0;
}
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    std::cerr << "Fork failed" << std::endl;
    return 1;
  }

  if (pid == 0) {
    // This block will be executed in the child process
    char *args[] = {(char *)"/bin/ls", (char *)"-l", NULL};
    execvp(args[0], args);                   // Executes the ls command
    std::cerr << "Exec failed" << std::endl; // Only gets here if exec failed
    return 1;
  } else {
    // This block will be executed in the parent process
    int status;
    waitpid(pid, &status, 0); // Wait for the child process to finish
    std::cout << "Child finished with status " << status << std::endl;
  }

  return 0;
}