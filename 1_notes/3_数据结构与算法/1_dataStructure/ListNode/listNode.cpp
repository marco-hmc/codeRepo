ListNode* reverse(ListNode* root) {
    ListNode* pre = nullptr, cur = root, nxt;
    while (cur != nullptr) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;cur = nxt;
    }
    return pre;
}

- ```c++
    // link:
    // https://leetcode-cn.com/problems/remove-linked-list-elements/submissions/
    // method1
    class Solution {
public:
  ListNode *removeElements(ListNode *head, int val) {
    ListNode *preHead = new ListNode(0);
    ListNode *pre = preHead;
    pre->next = head;
    ListNode *cur = head;
    while (cur != nullptr) {
      if (cur->val == val) {
        ListNode *next = cur->next;
        pre->next = next;
        cur = cur->next;
      } else {
        cur = cur->next;
        pre = pre->next;
      }
    }
    return preHead->next;
  }
};
// method2 注意这个方法是不行的
// 我想不出一个简洁的方式说明,读者自行体会.
class Solution {
public:
  ListNode *removeElements(ListNode *head, int val) {
    ListNode *pre = new ListNode(0);
    pre->next = head;
    ListNode *cur = head;
    while (cur != nullptr) {
      if (cur->val == val) {
        ListNode *next = cur->next;
        pre->next = next;
        cur = cur->next;
      } else {
        cur = cur->next;
        pre = pre->next;
      }
    }
    return head;
  }
};
```