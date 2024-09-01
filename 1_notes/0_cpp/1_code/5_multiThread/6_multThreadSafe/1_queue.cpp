#include <vector>
#include <condition_variable>
#include <mutex>
using namespace std;

// 实现一个队列, 并且使它支持多线程, 队列有什么应用场景(阿里三面)
class FIFOQueue {
private:
    vector<int> vec;
    int start;
    int end;
    int initCap;
    bool flag;
    condition_variable cv;
    mutex m;

public:
    FIFOQueue(int capacity) : vec(capacity), start(0), end(0), initCap(capacity), flag(false) {}

    bool enqueue(int v) {
        unique_lock<mutex>lk(m);
        while (flag == true) cv.wait(lk);
        end = (end + 1) % initCap;
        vec[end] = v;
        cv.notify_all();
        return true;
    }

    int dequeue() {
        unique_lock<mutex> lk(m);
        if (start != end) {
            int val = vec[start];
            start = (start + 1) % initCap;
            flag = false;
            cv.notify_all();
            return val;
        }
        else {
            flag = false;
            cv.notify_all();
            return -1;
        }
    }
};