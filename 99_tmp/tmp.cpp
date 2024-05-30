#include <iostream>

int main() {

  std::string str = "四 123";
  const char *cstr = "四 123";

  if (str.c_str() == cstr) {
    std::cout << "The strings are equal." << std::endl;
  } else {
    std::cout << "The strings are not equal." << std::endl;
  }
  // std::cout << *str.c_str() << std::endl;
  std::cout << str.c_str() << std::endl;
  std::cout << str << std::endl;

  if (str == cstr) {
    std::cout << "The strings are equal." << std::endl;
  } else {
    std::cout << "The strings are not equal." << std::endl;
  }
  return 0;
}

// #include <stdio.h>

// void f(unsigned char v)

// {

//   char c = v;

//   unsigned char uc = v;

//   unsigned int a = c, b = uc;

//   int i = c, j = uc;

//   printf("----------------\n");

//   printf("%%c: %c, %c\n", c, uc);

//   printf("%%X: %X, %X\n", c, uc);

//   printf("%%u: %u, %u\n", a, b);

//   printf("%%d: %d, %d\n", i, j);
// }

// int main(int argc, char *argv[])

// {

//   f(0x80);

//   f(0x7F);

//   return 0;
// }
