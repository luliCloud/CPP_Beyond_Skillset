/** 多线程写入和读取可以提高数据库的吞吐量，通过分离读和写线程，可以减少锁竞争 */
#include <iostream>
#include <string>
#include <thread> // 因为thread共享内存，所以需要mutex和条件变量等避免数据竞争和不一致问题
#include <mutex>
#include <condition_variable>
#include <map>
using namespace std;

class ThreadSafeMap {
private:
    map<string, string> mp;
    mutex mtx;
    condition_variable cv;
    bool ready = false;
public:
    void write(const string& key, const string& value) {
        unique_lock<mutex> lock(mtx);  // 注意区分lock 和 shared ptr
        mp[key] = value;
        ready = true;
        cv.notify_all(); // notify all threads
        // auto release mtx when leaving this func
    }

    string read(const string& key) {
        unique_lock<mutex> lock(mtx);
        /** 释放互斥锁：在调用 cv.wait 之前持有的互斥锁 mtx 会被释放，使得其他线程能够继续执行。
         * 这样，其他可能正在执行写操作的线程可以继续进行。等待通知：当前线程会进入等待状态，
         * 直到条件变量 cv 被其他线程通知（即调用 cv.notify_one 或 cv.notify_all），
         * 并且条件（return ready;）为 true。
重新获取锁：一旦收到通知并且条件满足，当前线程会尝试重新获取互斥锁 mtx，并从 cv.wait 返回，
继续执行后续的代码。 
只满足其中一个条件是无法确保程序正确执行的，因为通知只是表明条件可能已经改变，
而条件检查则是实际确认条件是否满足的关键步骤。这种双重机制可以避免假唤醒（spurious wakeup）的问题，
并确保线程同步的正确性。*/
        cv.wait(lock, [this]{ return ready; }); // waiting for writing finish. 一般会等到所有写入执行完
        return mp[key];
    }
};

int main() {
    ThreadSafeMap mp;
    /** &表示补货所有外部作用域中的额变量。（）是lambda的参数列表 
     * 在 lambda 表达式的函数体内编写需要在线程中执行的代码。
     * 将lambda表达式传递给thread 构造函数，创建并启动线程
    */
    thread writer([&](){ mp.write("key1", "value1"); });
    thread reader([&](){ 
        cout << "Read from map: " << mp.read("key1") << endl; 
    });
    writer.join();
    reader.join();
    return 0;
}