#include <iostream>

#include "Constants.h"

void printValueFromMain() {
    std::cout << "Value from main.cpp: " << value << ", Address: " << &value
              << std::endl;
}

void printValueFrom1();
void printValueFrom2();

int main() {
    printValueFromMain();
    printValueFrom1();
    printValueFrom2();
    return 0;
}