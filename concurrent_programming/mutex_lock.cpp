/** using mutex to lock thread */
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;

void safePrint(int n) {
    lock_guard<mutex> lock(mtx);  // 在作用域开始时自动加锁，在作用域结束时自动解锁
    cout << n << endl;
}

int main() {
    thread t1(safePrint, 1);
    thread t2(safePrint, 2);
    t1.join();
    t2.join();
    return 0;
}