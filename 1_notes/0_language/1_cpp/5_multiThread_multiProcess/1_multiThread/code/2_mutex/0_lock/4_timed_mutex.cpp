//         - `try_lock_for()`: 在指定的时间段内尝试获取互斥锁。如果在这个时间段内互斥锁变得可用，那么这个函数会获取锁并返回`true`。
//             如果时间段结束时互斥锁仍然不可用，那么这个函数会返回`false`。
//         - `try_lock_until()`: 在指定的时间点之前尝试获取互斥锁。如果在这个时间点之前互斥锁变得可用，那么这个函数会获取锁并返回`true`。
//             如果时间点到达时互斥锁仍然不可用，那么这个函数会返回`false`。

// 3. try_lock_for和try_lock_until的区别是什么？
//     `try_lock_for()`和`try_lock_until()`都是在指定的时间段内尝试获取互斥锁的函数。
//     `try_lock_for()`的形参是一个`std::chrono::duration`，表示等待的时间段。
//     `try_lock_until()`的形参是一个`std::chrono::time_point`，表示等待的截止时间。
//     两者的区别在于等待的时间段的表示方式不同。`try_lock_for()`表示等待的时间段是一个相对的时间段，从当前时刻开始计算。
//     `try_lock_until()`表示等待的时间点是一个绝对的时间点，是一个具体的时刻。

namespace identifier_try_lock {
    std::timed_mutex tmtx;

    void critical_section(int id) {
        if (tmtx.try_lock_for(std::chrono::milliseconds(100))) {
            std::cout << "Thread " << id << " entered critical section."
                      << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Thread " << id << " leaving critical section."
                      << std::endl;
            tmtx.unlock();
        } else {
            std::cout << "Thread " << id << " could not enter critical section."
                      << std::endl;
        }
    }

    void run() {
        std::thread t1(critical_section, 1);
        std::thread t2(critical_section, 2);

        t1.join();
        t2.join();
    }
}  // namespace identifier_try_lock