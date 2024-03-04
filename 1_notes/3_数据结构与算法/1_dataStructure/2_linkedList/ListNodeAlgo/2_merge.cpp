/* [21] 合并两个有序链表  */
#include <algorithm>
#include <climits>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// @lc code=start
class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    ListNode *dummyHead = new ListNode(0);
    ListNode *cur = dummyHead;
    while (list1 || list2) {
      int val1 = list1 ? list1->val : INT_MAX;
      int val2 = list2 ? list2->val : INT_MAX;
      int val = std::min(val1, val2);
      if (val == val1) {
        list1 = list1->next;
      } else {
        list2 = list2->next;
      }
      ListNode *tmp = new ListNode(val);
      cur->next = tmp;
      cur = cur->next;
    }
    return dummyHead->next;
  }
};
// @lc code=end
