/*
 * @Date: 2022-09-20 13:42:29
 * @LastEditors: Marco
 * @LastEditTime: 2022-09-20 13:47:41
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a(10, 1);
    vector<vector<int>> b(10, vector<int>(5, 0));
    sort(a.begin(), a.end(), 0);                  // 从小到大排序
    int sum = accumulate(a.begin(), a.end(), 0);  // 求和
    auto idx = find(a.begin(), a.end(), 2);       // 找a=2的的值
    a.erase(a.begin() + 1);                       // 删除第二个元素
}