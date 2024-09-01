#include <cassert>
#include <iostream>

template <typename T> class Deque {
private:
  T *arr;
  int capacity;
  int front;
  int rear;
  int size;

public:
  Deque(int capacity) {
    this->capacity = capacity;
    arr = new T[capacity];
    front = -1;
    rear = 0;
    size = 0;
  }

  ~Deque() { delete[] arr; }

  void push_front(T data) {
    if (isFull()) {
      std::cout << "Deque is full. Cannot push front." << '\n';
      return;
    }

    if (front == -1) {
      front = 0;
      rear = 0;
    } else if (front == 0) {
      front = capacity - 1;
    } else {
      front--;
    }

    arr[front] = data;
    size++;
  }

  void push_back(T data) {
    if (isFull()) {
      std::cout << "Deque is full. Cannot push back." << '\n';
      return;
    }

    if (front == -1) {
      front = 0;
      rear = 0;
    } else if (rear == capacity - 1) {
      rear = 0;
    } else {
      rear++;
    }

    arr[rear] = data;
    size++;
  }

  void pop_front() {
    if (isEmpty()) {
      std::cout << "Deque is empty. Cannot pop front." << '\n';
      return;
    }

    if (front == rear) {
      front = -1;
      rear = -1;
    } else if (front == capacity - 1) {
      front = 0;
    } else {
      front++;
    }

    size--;
  }

  void pop_back() {
    if (isEmpty()) {
      std::cout << "Deque is empty. Cannot pop back." << '\n';
      return;
    }

    if (front == rear) {
      front = -1;
      rear = -1;
    } else if (rear == 0) {
      rear = capacity - 1;
    } else {
      rear--;
    }

    size--;
  }

  T getFront() {
    if (isEmpty()) {
      std::cout << "Deque is empty. Cannot get front." << '\n';
      return T();
    }

    return arr[front];
  }

  T getBack() {
    if (isEmpty()) {
      std::cout << "Deque is empty. Cannot get back." << '\n';
      return T();
    }

    return arr[rear];
  }

  bool isEmpty() { return size == 0; }

  bool isFull() { return size == capacity; }
};

int main() {
  Deque<int> deque(5);

  deque.push_front(1);
  deque.push_front(2);
  deque.push_back(3);
  deque.push_back(4);

  assert(deque.getFront() == 2);
  assert(deque.getBack() == 4);

  deque.pop_front();
  deque.pop_back();

  assert(deque.getFront() == 1);
  assert(deque.getBack() == 3);

  std::cout << "All assertions passed!" << '\n';

  return 0;
}