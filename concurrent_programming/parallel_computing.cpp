/**
 * 任务并行（std::packaged, std::bind）: 任务并行允许将一个任务分解为多个子任务，并在多个线程上
 * 并行执行这些子任务。std：：packaged-task是一个封装了可调用对象的类，它可以被转换为std：：future
 */
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
using namespace std;

// a simaple task function
void process(int& num) {
    num *= 2;
}

int main() {
    vector<int> data = {1,2,3,4,5};
    /**
     * std::packaged_task 是一个模板类，它将一个可调用的对象封装成一个异步任务。
     * 这些任务可以被执行在不同的线程上，并且可以通过一个 std::future 对象来获取任务的执行结果。
     * 这里的模板参数 void() 指定了 packaged_task 包装的函数或可调用对象的类型，
     * 即一个不返回值（void）且不带参数的函数。
     * 
     * 你定义一个 vector<packaged_task<void()>>，你创建了一个能够存储多个这种类型的 packaged_task 
     * 对象的动态数组。每个 packaged_task 在这个数组中都可以独立地表示一个任务，
     * 这些任务可以被存储、传递、并在需要的时候执行。
     */
    vector<packaged_task<void()>> tasks; // 只是定义了tasks的内部元素类型，没有定义vector大小
    
    for (int& number : data) {
        /**
emplace_back 提供了一种更直接的方式来在容器中构建元素。它通过直接在容器内存中就地构造元素，
从而避免了复制或移动对象的额外成本。你可以直接传递构造函数的参数到 emplace_back，
它会使用这些参数在 vector 的末尾直接构造一个新元素。
使用 emplace_back 可以更有效地处理资源，尤其是对于那些不支持移动语义或资源昂贵的复制操作的对象。
它通过构造而非复制或移动来添加元素，减少了潜在的性能损耗。
         */
        // 创建任务
        // tasks.emplace_back(std::packaged_task<void()>([&]() { process(number); }));
        tasks.emplace_back(bind(process, ref(number))); // 报错说packaged_task 只能
        // move不能copy
        /**
         * bind 在这里就是将number和process预先绑定在一起。因为task中的对象是packaged-task，
         * pt只接受已构造的不接受参数的对象，而process又是一个需要参数的函数。所以需要bind。ref
         * 就是帮助process接受number的引用，否则bind默认穿参数是copy，违反了本意
         */

    }
    // 启动任务
    vector<future<void>> res;
    for (auto& task : tasks) {
        res.emplace_back(task.get_future()); // get_future return a future obj
        thread(move(task)).detach(); // 注意这里要使用move而不是直接copy task（可能thread
        // 默认是copy而不是移动，而task又是一个packaged-task，which 只能被移动。所以我们这里要用move）
            /** 这行代码做了两件事：
             * thread(task) 构造一个新的线程，并将 task 作为线程执行的函数。注意task就是packaged-task obj
             * 由于 std::packaged_task 本身是一个可调用对象，它可以直接被用作线程函数。
             * 
             * 与join相对，detach() 方法被调用在这个新创建的线程上。detach() 方法用于使线程在后台运行，一旦调用，
             * 控制权会从 std::thread 对象返回，允许线程独立于主线程继续运行。这意味着一旦 detach() 被调用，
             * 主线程不会等待这个线程结束，而是立即继续执行下一条指令。这通常用于那些不需要与主线程同步完成的任务。
             */
    }

    // 等待所有任务完成
    for (auto& f : res) {
        f.get(); // 因为是引用，所以会直接改变res中的future obj
    }

    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}

