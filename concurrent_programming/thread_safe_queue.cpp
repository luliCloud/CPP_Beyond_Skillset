/**
 * 线程安全队列：原理：通过互斥锁或其他同步机制保证在多线程环境下对队列的操作（入队和出队）是原子的，避免数据竞争
 * 实现：用std：：mutex来保护队列。std：：condition_variable 来同步线程间的操作
 */
#include <iostream>
#include <mutex>
#include <queue>
/** 当一个 std::condition_variable 对象被创建时，它的初始状态是未通知的。可以理解为条件变量一开始处于一种“没有任何线程等待”的状态。 */
#include <condition_variable>
using namespace std;

template <typename T>
class ThreadSafeQueue {
private:
    queue<T> queue_;
    mutable mutex mutex_;
    condition_variable cond_;
public:
    void push(T value) {
        lock_guard<mutex> lock(mutex_); // RAII。离开作用域时自动释放mutex
        /**
         * move是C++11新特性，将value转为右值引用，类似于&，避免深拷贝，同时转移了所有权给queue（注意不仅是value的值）
         * 通过使用移动语义move将对象传递给 queue，队列接管了该对象的内存管理。queue将在其生命周期中管理这个对象。
         * 而外部调用者（this）已经不再拥有这个对象的内存管理权。引用&是不可以的。&只能用于修改（避免深拷贝），
         * 但是所有权依然属于函数调用者。
         */
        queue_.push(move(value));
        cond_.notify_one();  // 这里会通知在等待的线程（由另一个函数pop（）中的cond_在管理）
    }

    T pop() {
        /**
         * std::lock_guard：在构造时立即锁定，且在析构时解锁，无法手动控制锁的状态。
std::unique_lock：可以在构造时选择立即锁定或延迟锁定，并且可以手动锁定和解锁。（lock and unlock）
         */
        unique_lock<mutex> lock(mutex_);
        // cond_ wait, until the queue is not empry, it will be wake up
        // cond_ 实际上是使线程在等待状态。当return为false时，会释放锁，并让线程等待。
        /**
         * 成员变量不是全局作用域或本地作用域中的变量。
         * 因此，当你在类的成员函数中使用 lambda 表达式时，需要通过捕获 this 指针来访问这些成员变量。
         */
        cond_.wait(lock, [this]{ return !queue_.empty(); });
        
        T value = move(queue_.front()); // 将所有权再次转交给value
        queue_.pop();
        return value;
    }

    bool empty() const { // this is way we make mutex mutable, it will be includes in the const func
        // to ensure the atomic of every operation, we need to lock mutex in every function
        lock_guard<mutex> lock(mutex_);
        return queue_.empty();
    }
};

int main() {
    /**
     * ThreadSafeQueue<int> 是一个模板类的实例化，其中 int 是模板参数。这意味着 ThreadSafeQueue 是一个模板类，
     * 可以接受不同的数据类型作为参数来创建不同类型的队列。在这个例子中，int 是模板参数，表示这个队列将存储 int 类型的元素。
     */
    ThreadSafeQueue<int> tsQueue;
    tsQueue.push(1);
    int value = tsQueue.pop();
    cout << "Popped value: " << value << endl;
    return 0;
}
