#include <iostream>
#include <functional>
using namespace std;

void func1(int n1, int n2, int n3){
    cout << n1 << " " << n2 << " " << n3 << endl;
}

int main(){
    auto f1 = bind(func1, placeholders::_2, 22, placeholders::_1);
    f1(11, 33);
    cout << "done" << endl;
    return 0;
}