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
    /** t1 obtained mtx enter while loop (as ready is false now). As cv is wait, t1 release mtx. 
     * t2 do similar thing and also in while loop. mtx is free now  */
    unique_lock<mutex> lock(mtx);
    while (!ready) {
        /** the mtx is release and current thread is temporarily hang out */
        cv.wait(lock);
    }
    cout << "Thread " << id << endl;
}

int main() {
    thread t1(printID, 1);
    thread t2(printID, 2);
    /** mtx is free now */
    {
        /** main thread obtain the mtx, change ready to true, leave the block and release mtx */   
        lock_guard<mutex> lock(mtx);
        ready = true;
    }
    /** notify cv (and all realted threads) that ready is true */
    cv.notify_all();
    /** all threads try to obtain mtx again. the first thread obtain mtx again */
    t1.join();
    t2.join();
    return 0;
}