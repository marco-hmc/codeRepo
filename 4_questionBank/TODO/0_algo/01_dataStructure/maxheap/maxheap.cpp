/*
 * @Date: 2022-09-20 13:43:02
 * @LastEditors: Marco
 * @LastEditTime: 2022-09-22 22:55:56
 */
// main.cpp
#include "maxheap.h"
#include <iostream>

using namespace std;
int main() {
    Maxheap<int> H(100);  //创建容量为100的堆
    H.push(20);
    H.push(30);
    H.push(15);
    H.push(40);
    H.push(90);
    cout << "堆顶元素为：" << H.top() << endl;
    H.pop();
    cout << "堆顶元素为：" << H.top() << endl;
    system("pause");
    return 0;
}
