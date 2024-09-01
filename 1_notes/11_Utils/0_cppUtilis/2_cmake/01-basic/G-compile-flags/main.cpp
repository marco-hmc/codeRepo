#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << "Hello Compile Flags!" << '\n';

  // only print if compile flag set
#ifdef EX2
   std::cout << "Hello Compile Flag EX2!" << '\n';
#endif

#ifdef EX3
  std::cout << "Hello Compile Flag EX3!" << '\n';
#endif

   return 0;
}
