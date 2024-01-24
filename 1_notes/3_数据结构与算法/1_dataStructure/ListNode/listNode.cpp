ListNode* reverse(ListNode* root) {
    ListNode* pre = nullptr, cur = root, nxt;
    while (cur != nullptr) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;cur = nxt;
    }
    return pre;
}