/** advanced concurrent programming I
 * 异步I/O是一种允许程序在等待I/O操作完成时继续执行其他任务的技术。std::async启动一个异步任务，
 * 可以在另一个线程中运行，并返回一个std：：future对象，在将来需要时用于捕获异步操作的结果
 */
#include <iostream>
#include <future>
#include <thread>
using namespace std;

int asyncTask() {
    this_thread::sleep_for(chrono::seconds(1));
    return 42;
}

int main() {
    future<int> res = async(asyncTask); // don't add () after function Name
    /**
     * 获取结果：get() 方法阻塞调用线程，直到异步操作完成并且结果可用。只有当异步任务完成后，
     * get() 会返回其结果。如果异步任务已经完成，get() 会立即返回结果。

同步点：调用 get() 方法的位置成为代码中的一个同步点。这意味着在这一点上，主线程将等待异步任务的完成，
只等待该异步任务，不保证其他异步任务。确保在输出结果之前，相关的计算已经完成。

一次性：get() 方法只能被调用一次。一旦调用 get() 获取了结果，该future 对象就不能再次用来获取结果。
如果再次调用 get()，将会引发异常。
     */
    cout << "REsult from async task is: " << res.get() << endl;
    return 0;
}