/** using conditional variable to synchronize threads */
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void printID(int id) {
    unique_lock<mutex> lock(mtx);
    /** cv 会用return ready的结果来判断是否结束等待，重新获得lock。这一句的意思是，如果return ready结果为false，
     * 那么cv会释放lock，等待ready的结果便为true。当 return ready结果便为true时，cv会重新获得mtx进行后面的程序
     * 要注意的是，cv只能wait lock，不能wait ready。cv会不断的检查return ready的结果，如果这个lambda语句写在wait里面
     * 否则它不会不断检查。而是需要我们像另一问中的一样，写一个while
     * while (!ready) { cv.wait(lock); }
     */
    cv.wait(lock, []{ return ready; });
    cout << "Thread " << id << endl;
}

int main() {
    thread  t1(printID, 1);
    {
        lock_guard<mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();
    t1.join(); // 主线程会等待t1执行完，再执行主线程后续的代码。所以join不是开始t1，而是等待t1
    return 0;
}