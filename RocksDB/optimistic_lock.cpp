/** 并发控制机制确保在多线程环境下数据的一致性和完整性。常见的并发控制方法有乐观锁 optimistic lock
 * 和悲观锁 pessimistic lock
 */
/** 乐观锁通常用于写入不频繁的场景，通过版本号来确保在读取到写入期间数据没有被其他线程修改 
 * 观锁定假设数据的大部分时间不会发生冲突，因此在执行写操作前不加锁，
 * 而是在操作完成后检查是否有其他线程修改过数据。如果发现冲突，
 * 则放弃当前操作（通过 compare_exchange_weak 返回 false），由调用者决定如何处理（例如重试操作）。
*/
#include <iostream>
#include <unordered_map>
#include <atomic>
using namespace std;

class ConcurrentKeyValueStore {
private:
    unordered_map<string, string> store;
    /* atomic 是 C++11 引入的模板类，位于头文件 <atomic> 中。它提供了对基础数据类型的原子操作支持，
    可以保证在多线程环境下对变量的操作是线程安全的。int 是模板参数，指定了该原子类型变量存储的是整数类型
    的数据。在多线程编程中，多个线程可能会同时读取和修改同一个变量。使用 atomic<int> 可以确保这些操作是原子的，
    也就是说，它们不会被中断，确保了数据的一致性和正确性。
    变量名 version 通常用于版本控制场景，比如在实现乐观锁时，version 可以用来跟踪数据的版本号，
    以检测数据是否被修改过。*/
    atomic<int> version = 0;
public:
    bool put(const string& key, const string& value) {
        int currentVersion = version.load(); // actomic的load是线程安全的
        // execute write opt
        store[key] = value; // 注意这一步并不是线程安全的，我们假设他是线程安全的
        // update version num
        /** 尝试将version的值从current Version更新为Current Version + 1。 weak是一个原子操作
         * 只有当version的当前值等于current Version时，才会将version更新。并返回true
         * 这种方法用于实现乐观锁定，确保执行写操作期间没有被其他线程修改过version
         */
        return version.compare_exchange_weak(currentVersion, currentVersion + 1);
    }

    string get(const string& key) {
        int currentVersion = version.load();
        // if version num is unchanged during reading , read the data
        if (currentVersion = version.load()) {
            return store[key];
        }
        return ""; // data might be changed by other process
    }
};

int main() {
    ConcurrentKeyValueStore store;
    store.put("Key1", "Value1");
    cout << "Get Key1: " << store.get("Key1") << endl;
    return 0; 
}