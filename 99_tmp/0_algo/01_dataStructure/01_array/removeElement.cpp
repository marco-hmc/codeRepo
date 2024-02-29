/*
 * @Author: marco-hmc marco_hmc@163.com
 * @Date: 2023-01-30 15:43:08
 * @LastEditors: marco-hmc marco_hmc@163.com
 * @LastEditTime: 2023-01-31 12:30:07
 * @FilePath: \0_algo\01_dataStructure\01_array\removeElement.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int calculate(vector<int> nums, int target){
        int n = nums.size();
        int l = 0;
        for (int r = 0; r < n; r++){
            if(nums[r] != target) {
                nums[l] = nums[r];
                l++;
            }
        }
        return l;
    }
};

int main() {
    vector<int> a{3,2,2,3};
    int target = 3;
    Solution s;
    cout << s.calculate(a, target) << endl;
    return 0;
}
