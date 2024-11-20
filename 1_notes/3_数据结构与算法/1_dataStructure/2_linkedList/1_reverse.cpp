struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int val) : val(val) {}
};

class Solution {
  public:
    ListNode *ReverseList(ListNode *head) {
        ListNode *cur = head;
        ListNode *pre = nullptr;
        while (cur != nullptr) {
            ListNode *nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }
};

int main() {}