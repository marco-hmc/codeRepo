#include <iostream>

class Queue {
private:
  static const int MAX_SIZE = 100;
  int arr[MAX_SIZE];
  int front;
  int rear;

public:
  Queue() {
    front = -1;
    rear = -1;
  }

  bool isEmpty() { return front == -1 && rear == -1; }

  bool isFull() { return rear == MAX_SIZE - 1; }

  void enqueue(int value) {
    if (isFull()) {
      std::cout << "Queue is full. Cannot enqueue." << std::endl;
      return;
    }

    if (isEmpty()) {
      front = 0;
      rear = 0;
    } else {
      rear++;
    }

    arr[rear] = value;
  }

  void dequeue() {
    if (isEmpty()) {
      std::cout << "Queue is empty. Cannot dequeue." << std::endl;
      return;
    }

    if (front == rear) {
      front = -1;
      rear = -1;
    } else {
      front++;
    }
  }

  int getFront() {
    if (isEmpty()) {
      std::cout << "Queue is empty." << std::endl;
      return -1;
    }

    return arr[front];
  }

  int getRear() {
    if (isEmpty()) {
      std::cout << "Queue is empty." << std::endl;
      return -1;
    }

    return arr[rear];
  }
};

int main() {
  Queue queue;
  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);
  std::cout << "Front: " << queue.getFront() << std::endl;
  std::cout << "Rear: " << queue.getRear() << std::endl;

  queue.dequeue();
  std::cout << "Front: " << queue.getFront() << std::endl;
  std::cout << "Rear: " << queue.getRear() << std::endl;

  return 0;
}