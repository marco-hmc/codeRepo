#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int calculate(vector<int> nums, int target){
        // int l, r = 0, nums.size();
        int l = 0, r = nums.size();
        while(l<r){
            int mid = (l + r) / 2;
            if(nums[mid] == target){
                return mid;
            }else if(nums[mid] < target){
                l = mid;
            }else if(nums[mid] > target){
                r = mid;
            }
        }
        return -1;
    }
};

int main() {
    vector<int> a{-1, 0, 3, 5, 9, 12};
    int target = 9;
    Solution s;
    cout << s.calculate(a, target) << endl;
    return 0;
}
