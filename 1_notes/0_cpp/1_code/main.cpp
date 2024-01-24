#include <iostream>
#include <vector>

using namespace std;
template <typename T> struct type_identity { using type = T; };

int main() {
    type_identity<char>::type;
    return 0;
}