#include <bits/stdc++.h>
using namespace std;

class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        queue.reserve(k);
        size = k;
        head = -1;
        tail = -1;
    }
    
    bool enQueue(int value) {
        if (isEmpty()) {
            head++;
            tail++;
            queue[tail] = value;
            return true;
        }
        else if (isFull()) return false;
        tail = (tail + 1) % size;
        queue[tail] = value;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        if (head == tail) {
            head = -1;
            tail = -1;
            return true;
        }
        head = (head + 1) % size;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return queue[head];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return queue[tail];
    }
    
    bool isEmpty() {
        if (head == -1 && tail == -1) return true;
        return false;
    }
    
    bool isFull() {
        if ((tail + 1) % size == head) return true;
        return false;
    }

private:
    vector<int> queue;
    int size;
    int head;
    int tail;
};

// 作者：GeekLee
// 链接：https://leetcode.cn/leetbook/read/queue-stack/kzlb5/?discussion=8COoog
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。