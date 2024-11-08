#include <iostream>
#include "ver.h"
#include "path.h"

int main(int argc, char *argv[])
{
  std::cout << "Hello Version " << ver << "!" << '\n';
  std::cout << "Path is " << path << '\n';
  return 0;
}
