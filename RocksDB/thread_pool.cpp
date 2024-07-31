#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cond;
    bool stop = false;
public:
    // 添加任务到线程池
    /**function<void()> task 是 C++11 引入的标准库类型 std::function 的一个实例。std::function 
     * 是一个通用、多态的函数封装器，
     * 可以存储、复制和调用任何可调用目标（如普通函数、lambda 表达式、函数对象和成员函数）。 
     * 这里function中确定了是void（），表示被封装的课调用对象一定是函数，且不接受任何参数不返回任何值*/
    void addTask(function<void()> task) {
        lock_guard<mutex> lock(mtx);
        tasks.push(task);
        cond.notify_one();
    }

    // 线程池工作线程运行的函数
    void worker() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(mtx);
                // 一开始都是处于等待状态，等待tasks中开始有task。注意区分workers和tasks
                cond.wait(lock, [this]{ return !tasks.empty() || stop; }); // 队列为空或者stop唤醒
                if (stop && tasks.empty()) return;
                task = move(tasks.front()); // move是将对象的所有权从一个变量转移到另一个变量。front
                // 返回第一个元素的引用。移动操作完成后，队列中的第一个元素处理有效但未指定的状态（nullptr？）
                // 其值已经被转移，但它仍位于队列中。
                tasks.pop();
            }
            task(); // execute task
        }
    }

    // start thread pool
    void start(int numThreads) {
        for (int i = 0; i < numThreads; i++) {
            // 当你传递 &ThreadPool::worker 作为线程函数时，它只是一个成员函数指针，需要一个对象实例来调用它。
            // this 指针提供了这个对象实例，使得成员函数可以在该实例上执行。成员函数与普通函数不一样，必须要有
            // 实例来调用才能运行。
            // 如果不使用 &，代码将无法编译，因为 ThreadPool::worker 将被视为成员函数声明，而不是成员函数指针
            // 不能写成workds.emplace_back(worker, this); 因为worker是成员函数，必须由实例调用，并声明属于哪个类。
            // 否则无法与实例关联

            workers.emplace_back(&ThreadPool::worker, this); // 直接给线程池传入线程
            // 这个线程的构造在emplace back中进行，worker是thread的构造函数中的函数，this是调用这个函数的实例
        }
    }

    // 停止线程池
    void stop_() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
            cond.notify_all();
        }
        for (thread& worker : workers) {
            worker.join();
        }
    }
};

int main() {
    ThreadPool pool;
    pool.start(4); // 创建四个工作线程。这时候都在等待，因为tasks中是没有task（函数）的

// 当tasks中开始添加task后，线程就会启动。lambda函数就是传入addTask中的function<void()> task
// 这里在tasks 中加入task后，workers中在等待的四个线程就是开始运作。其中一个唤醒。
// 注意这两个task应该是几乎同时加入tasks队列中。所以不存在处理完第一个就因为stop return
// 另外注意worker中才是线程池。
    pool.addTask(
        []() { cout << "Task1 executed by thread " << this_thread::get_id() << endl; }
    );

    pool.addTask(
        []() { cout << "Task2 executed by thread " << this_thread::get_id() << endl; }
    );
    pool.stop_();
    return 0;
}