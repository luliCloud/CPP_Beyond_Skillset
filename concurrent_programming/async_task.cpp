/** C++ 11
 * 异步任务 std::async 允许启动一个异步操作，其结果是可以通过std::future 获取
 * 未来对象： std::future 用于获取异步操作的结果
 */
#include <iostream>
#include <future>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

int asyncFunction() {
    return 42;
}

/** a more complicated example */
int asyncFunction2(int x) {
    this_thread::sleep_for(chrono::seconds(x)); // similuate time consuming
    // cout << "in duration " << x << endl; 
    return x * x;
}

int main() {
    /** 这里async立即启动了asyncFunction （可能在后台或者另一个线程中），
     * 但是结果在这一步并不一定返回给了result。程序会接着往下执行。所以result只是表明将来会有一个结果 */
    future<int> result = async(asyncFunction);
    
    // main thread 在执行，async也在后台另一个thread执行。

    /** 在我们用result。get时，就一定要拿到结果了。所以这是get会阻塞住main thread */
    cout << "Result from async function: " << result.get() << endl;

    // for more complicated example
    vector<future<int>> futures;
    // initialize several task
    for (int i = 1; i <= 5; i++) {
        futures.push_back(async(launch::async, asyncFunction2, i));  // for taking arg
    }

    // output all result
    for (auto& f : futures) {  // must be referenced
        cout << f.get() << endl;
    }
    cout << endl;
    return 0;
}
/** output will be print in 5 seconds. each second print 1 number 
 * Result from async function: 42
1
4
9
16
25
*/