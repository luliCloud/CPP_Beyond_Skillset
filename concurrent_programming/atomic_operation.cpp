/** std::atomic  from C++11 stl
 * 提供一种无需互斥锁的方法即可安全的在多线程间共享数据
 */
#include <iostream>
#include <atomic>  // noting not actomic
#include <thread>
using namespace std;

/**
 * 先理解一下内存重排序，方便理解什么是memory_order_relaxed
 * 即我们在线程1中执行的顺序，并不一定是在线程2中会看到的顺序。只保证count1这一步的原子性，即线程2要么看到count1没有执行
 * 的结果，要么看到count1执行完的结果，不会看到它内部的中间结果
 */
int x = 0;
std::atomic<int> count1(0);

void thread1() {
    x = 42;
    count1.fetch_add(1, std::memory_order_relaxed);
}

void thread2() {
    while (count1.load(std::memory_order_relaxed) == 0) {}
    std::cout << x << std::endl; // x 的值可能不是 42
}
/** this is real code */
/** atomic is a template. ct is a type of atomic<int>, we set the ct value initialized as 0 
 * ct 是一个 std::atomic<int> 类型的变量，初始值为 0。这个变量在多个线程中可以被安全地读取和修改，
 * 而无需显式的锁机制（如 mutex）。
*/
atomic<int> ct(0);
void increament() {
    // ct.fetch_add make the ct value++, and return old value. it is an atomic op
    // memory_order_relaxed 是一种内存排序策略，表示不需要对操作进行任何同步或顺序上的约束。即，
    // 操作的顺序可以被重排序，但不会影响单个线程内的执行顺序。(编译器和系统有时为了追求high performance，会重排内存的操作顺序)
    ct.fetch_add(1, memory_order_relaxed);
}

int main() {
    thread t1(increament);
    thread t2(increament);
    t1.join();
    t2.join();
    cout << "Final count " << ct << endl;
    return 0;
}
