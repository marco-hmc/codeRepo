struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
class Solution2 {
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

#include <iostream>

int main() {
  // Create a linked list
  ListNode *head = new ListNode(1);
  ListNode *node1 = new ListNode(2);
  ListNode *node2 = new ListNode(3);
  ListNode *node3 = new ListNode(4);
  ListNode *node4 = new ListNode(5);
  head->next = node1;
  node1->next = node2;
  node2->next = node3;
  node3->next = node4;

  // Create an instance of Solution
  Solution solution;

  // Test method1
  ListNode *result1 = solution.removeElements(head, 3);
  std::cout << "Method1 Result: ";
  while (result1 != nullptr) {
    std::cout << result1->val << " ";
    result1 = result1->next;
  }
  std::cout << std::endl;

  // Test method2
  Solution2 solution2;
  ListNode *result2 = solution2.removeElements(head, 3);
  std::cout << "Method2 Result: ";
  while (result2 != nullptr) {
    std::cout << result2->val << " ";
    result2 = result2->next;
  }
  std::cout << std::endl;

  return 0;
}