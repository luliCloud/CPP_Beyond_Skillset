/** 性能基准测试用于评估数据库系统在不同工作负载下的性能表现 */
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void benchmark() {
    auto start = chrono::high_resolution_clock::now();

     // mimic the database manipulation 
    this_thread::sleep_for(chrono::seconds(1)); // mimic time consuming op
    
    auto end  = chrono::high_resolution_clock::now();  // record the ending time use now
    chrono::duration<double> elapse = end - start;
    cout << "Bencahmark took " << elapse.count() << " seconds" << endl;
}

int main() {
    benchmark();
    return 0;
}
/** Bencahmark took 1.00012 seconds */