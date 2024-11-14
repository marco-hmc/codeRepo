#include <bits/stdc++.h>

struct Node {
    float data;
    Node* next;
};

void selectionSort(Node* head) {
    Node* temp = head;

    while (temp != nullptr) {
        Node* m = temp;
        Node* r = temp->next;

        while (r != nullptr) {
            if (m->data > r->data) m = r;
            r = r->next;
        }

        float x = temp->data;
        temp->data = m->data;
        m->data = x;
        temp = temp->next;
    }
}

void bucket_sort(float arr[], int n) {
    std::vector<Node*> bucket(n, nullptr);
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];
        Node* newNode = new Node();
        newNode->data = arr[i];
        newNode->next = nullptr;
        if (bucket[bi] == nullptr) {
            bucket[bi] = newNode;
        } else {
            Node* temp = bucket[bi];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    for (int i = 0; i < n; i++) {
        selectionSort(bucket[i]);
    }
    int ct = 0;
    for (int i = 0; i < n; i++) {
        while (bucket[i] != nullptr) {
            arr[ct] = bucket[i]->data;
            ct++;
            bucket[i] = bucket[i]->next;
        }
    }
    for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
}

int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << n << std::endl;
    bucket_sort(arr, n);
    return 0;
}
