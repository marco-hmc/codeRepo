#include <vector>
using namespace std;

void insertSort(vector<int>& nums) {
    int len = nums.size();
    for (int i = 1;i < len;i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 and nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}