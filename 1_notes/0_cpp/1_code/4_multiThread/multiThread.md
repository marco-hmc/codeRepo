#### C++写一个线程池框架(list/queue/conditional),多线程操作,C++面向对象建模和多态以及单元测试
CPU之间的负载调度/做异步编程/非阻塞线程的拓展思路/非阻塞线程与可阻塞线程之间死锁关系.

#### 生产者消费者消息队列 线程

* * **一/多机数据处理**.

  有 10 台机器,每台机器上保存着 10 亿个 64-bit 整数(不一定刚好 10 亿个,可能有上下几千万的浮动),一共约 100 亿个整数(其实一共也就 80GB 数据,不算大,选这个量级是考虑了 VPS 虚拟机的容量,便于实验).编程求出:

  \1. 这些数的平均数.

  \2. 这些数的中位数.

  \3. 出现次数最多的 100 万个数.

  *4. (附加题)对这 100 亿个整数排序,结果顺序存放到这 10 台机器上.

  *5. (附加健壮性要求)你的程序应该能正确应对输入数据的各种分布(均匀/正态/Zipf).

  *6. (附加伸缩性要求)你的程序应该能平滑扩展到更多的机器,支持更大的数据量.比如 20 台机器/一共 200 亿个整数,或者 50 台机器/一共 500 亿个整数.

* **二/N-皇后问题的多机并行求解**.利用多台机器求出 N-皇后问题有多少个解.(注意目前的世界纪录是 N = 26,[A000170 - OEIS](https://link.zhihu.com/?target=http%3A//oeis.org/A000170) )

  \1. 8 皇后问题在单机上的运算时间是毫秒级,有 92 个解,编程实现之.

  \2. 研究 N-皇后问题的并行算法,写一个单机多线程程序,争取达到线性加速比(以 CPU 核数计).再设法将算法扩展到多机并行.

  \3. 用 10 台 8 核的机器(一共 80 个 CPU cores),求解 19-皇后和 20-皇后问题,看看分别需要多少运行时间.你的方案能否平滑扩展到更多的机器?

  *4. (附加题)如果这 10 台机器的型号不一,有 8 核也有 16 核,有旧 CPU 也有更快的新 CPU,你该采用何种负载均衡策略,以求缩短求解问题的时间(至少比 plain round-robin 算法要好)?


#### (3) 写三个线程交替打印ABC
```C++
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex mymutex;
condition_variable cv;
int flag=0;

void printa(){
    unique_lock<mutex> lk(mymutex);
    int count=0;
    while(count<10){
        while(flag!=0) cv.wait(lk);
        cout<<"thread 1: a"<<endl;
        flag=1;
        cv.notify_all();
        count++;
    }
    cout<<"my thread 1 finish"<<endl;
}
void printb(){
    unique_lock<mutex> lk(mymutex);
    for(int i=0;i<10;i++){
        while(flag!=1) cv.wait(lk);
        cout<<"thread 2: b"<<endl;
        flag=2;
        cv.notify_all();
    }
    cout<<"my thread 2 finish"<<endl;
}
void printc(){
    unique_lock<mutex> lk(mymutex);
    for(int i=0;i<10;i++){
        while(flag!=2) cv.wait(lk);
        cout<<"thread 3: c"<<endl;
        flag=0;
        cv.notify_all();
    }
    cout<<"my thread 3 finish"<<endl;
}
int main(){
    thread th2(printa);
    thread th1(printb);
    thread th3(printc);

    th1.join();
    th2.join();
    th3.join();
    cout<<" main thread "<<endl;
}
```