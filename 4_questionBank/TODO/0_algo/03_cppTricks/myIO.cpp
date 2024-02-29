/*
 * @Date: 2022-09-20 13:42:36
 * @LastEditors: Marco
 * @LastEditTime: 2022-09-20 14:13:37
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    do {
        getline(cin, str, '\n');
    } while (!str.empty());
    
    str = "1, 2, 3, 4";
    istringstream out(str);
    int num;
    while (out >> num) {
        cout << num << endl;
    }
    return 0;
}