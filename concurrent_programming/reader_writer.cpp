/**
 * 读者-写者模式是一种用于控制对共享资源的并发访问的模式。适用于读操作员多于写操作的场景。
 * 在这个场景中，多个读者可以同时发昂问资源，但写着在写入资源时需要独占访问权。写者在写入前需要等待所有读者完成读取
 * （如何保证？没看出来）
 * shared_mutex: 允许多个共享（读）锁或一个独占（写）锁
 * condition_variable: 用于同步读者和写者，确保写者在所有读者完成后写入
 * 
 * shared_mutex: 一个读进行时，其他读进程可以进来，继续hold住shared mutex。
 * 但是写锁不可以进来。所以这样会等到所有读锁都占完再进来写锁。
 * 但是如果读锁刚好断开呢？写锁会进来，但这也正好说明在写锁进来那一刻读thread已经没有了
 * 
 * 关于读锁的释放和写锁的获取，有以下几点细节需要注意：

写锁等待读锁释放：当有线程请求写锁时，它会等待所有现有的读锁都被释放。
这期间，【不会】有新的读锁被授予（就是已有的读锁可以被更多读请求进入），
从而避免了写锁长时间等待的问题。
 */

#include <iostream>
#include <shared_mutex>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

class SharedData {
private:
    shared_mutex rw_mutex_;
    int data_;
public:
    void write(int value) {
        unique_lock<shared_mutex> lock(rw_mutex_); // noting here is unique_lock
        cout << "Writing "<< value << endl;
        data_ = value;
        // simulate write delay
        this_thread::sleep_for(chrono::seconds(1));
    }

    int read() {
        shared_lock<shared_mutex> lock(rw_mutex_); // here is shared_lock for read
        cout << "Reading " << data_ << endl;
        // simiulate read delay
        this_thread::sleep_for(chrono::seconds(1));
        return data_;
    }
};

int main() {
    SharedData sd;

    thread writer[1];
    thread reader[3];

    for (int i = 0; i < 1; i++) {
        /**
         * 是的，确切地说，当你在 lambda 函数的捕获列表中使用 & 时，
         * 它会通过引用捕获 lambda 函数外部作用域中的所有变量。
         * 这允许 lambda 函数访问和修改这些外部变量。在你的例子中，如果 sd 是定义在 lambda 
         * 外部的一个对象，那么使用 & 将允许 lambda 函数通过引用来访问 sd，
         * 并调用其 write 方法。这是一种常见的方式，特别是在需要多线程操作外部变量或对象时。
         */
        writer[i] = thread([&](){ return sd.write(42); });
    }

    for (int i = 0; i < 3; i++) {
        reader[i] = thread([&](){return sd.read(); });
    }

    writer[0].join();
    for (int i = 0; i < 3; i++) {
        reader[i].join();
    }

    return 0;
}