/*
 * @Author: marco-hmc marco_hmc@163.com
 * @Date: 2023-01-30 15:43:08
 * @LastEditors: marco-hmc marco_hmc@163.com
 * @LastEditTime: 2023-01-31 13:15:21
 * @FilePath: \0_algo\01_dataStructure\01_array\removeElement.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    vector<int> calculate(vector<int> nums){
        int n = nums.size();
        vector<int> ret(n, 0);
        int l = 0, r=n-1;
        for (int i = n-1; i >= 0; i--){
            if(nums[r] * nums[r] >= nums[l] * nums[l]){
                ret[i] = nums[r] * nums[r];
                r--;
            }else{
                ret[i] = nums[l] * nums[l];
                l++;
            }
        }
        return ret;
    }
};

int main() {
    vector<int> a{-4,-1,0,3,10};
    Solution s;
    vector<int> ret = s.calculate(a);
    return 0;
}
