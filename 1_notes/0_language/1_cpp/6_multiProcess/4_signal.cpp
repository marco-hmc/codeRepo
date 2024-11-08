#include <csignal>
#include <iostream>

// Signal handler function
void signalHandler(int signal) {
  std::cout << "Received signal: " << signal << '\n';
}

int main() {
  // Register signal handler
  signal(SIGINT, signalHandler);

  std::cout << "Running..." << '\n';

  // Infinite loop to keep the program running
  while (true) {
    // Do some work here
  }

  return 0;
}