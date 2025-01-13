#include <cassert>
#include <iostream>

using namespace std;

void poorSon1(double *value) {
    cout << &value << endl;
    *value = *value + 1;
}

void fater(double *value) {
    cout << &value << endl;
    *value = *value + 1;
    poorSon1(value);
}

void poorSon2(double **value) { *value = *value + 1; }

int main() {
    double value = 0.0;
    cout << &value << endl;
    fater(&value);
    cout << value << endl;
    return 0;
}