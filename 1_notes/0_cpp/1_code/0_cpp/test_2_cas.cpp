#include <catch2/catch.hpp>
#include "StringWithoutCopyAndSwap.h"

TEST_CASE("StringWithoutCopyAndSwap - Constructor and c_str") {
    const char* str = "Hello, World!";
    StringWithoutCopyAndSwap s(str);
    REQUIRE(strcmp(s.c_str(), str) == 0);
}

TEST_CASE("StringWithoutCopyAndSwap - Copy Constructor") {
    const char* str = "Hello, World!";
    StringWithoutCopyAndSwap s1(str);
    StringWithoutCopyAndSwap s2(s1);
    REQUIRE(strcmp(s2.c_str(), str) == 0);
}

TEST_CASE("StringWithoutCopyAndSwap - Assignment Operator") {
    const char* str1 = "Hello";
    const char* str2 = "World";
    StringWithoutCopyAndSwap s1(str1);
    StringWithoutCopyAndSwap s2(str2);
    s2 = s1;
    REQUIRE(strcmp(s2.c_str(), str1) == 0);
}

TEST_CASE("StringWithoutCopyAndSwap - Destructor") {
    const char* str = "Hello, World!";
    {
        StringWithoutCopyAndSwap s(str);
        // Do nothing, just test if the destructor is called without any issues
    }
    // If the destructor is implemented correctly, there should be no memory leaks or crashes
    REQUIRE(true);
}