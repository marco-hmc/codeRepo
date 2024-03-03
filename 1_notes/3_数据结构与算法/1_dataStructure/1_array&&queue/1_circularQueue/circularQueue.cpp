#include <iostream>
#include <vector>

using namespace std;

class MyCircularQueue {
public:
  MyCircularQueue(int k) : size(k), head(-1), tail(-1) { queue.reserve(k); }

  bool enQueue(int value) {
    if (isEmpty()) {
      head++;
      tail++;
    } else if (isFull())
      return false;
    tail = (tail + 1) % size;
    queue[tail] = value;
    return true;
  }

  bool deQueue() {
    if (isEmpty())
      return false;
    if (head == tail) {
      head = -1;
      tail = -1;
    } else {
      head = (head + 1) % size;
    }
    return true;
  }

  int Front() {
    if (isEmpty())
      return -1;
    return queue[head];
  }

  int Rear() {
    if (isEmpty())
      return -1;
    return queue[tail];
  }

  bool isEmpty() { return (head == -1 && tail == -1); }

  bool isFull() { return ((tail + 1) % size == head); }

private:
  vector<int> queue;
  int size;
  int head;
  int tail;
};
int main() {
  // Create a circular queue with size 5
  MyCircularQueue cq(5);

  // Enqueue elements into the circular queue
  cq.enQueue(1);
  cq.enQueue(2);
  cq.enQueue(3);
  cq.enQueue(4);
  cq.enQueue(5);

  // Try to enqueue one more element (should return false)
  bool enqueued = cq.enQueue(6);
  if (!enqueued) {
    cout << "Circular queue is full. Cannot enqueue." << endl;
  }

  // Dequeue elements from the circular queue
  cq.deQueue();
  cq.deQueue();

  // Get the front and rear elements of the circular queue
  int front = cq.Front();
  int rear = cq.Rear();

  cout << "Front element: " << front << endl;
  cout << "Rear element: " << rear << endl;

  return 0;
}