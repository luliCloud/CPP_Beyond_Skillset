/** create and initiate thread */
#include <iostream>
#include <thread>
using namespace std;
void threadFunction() {
    cout << "Hello from thread!" << endl; 
}

int main() {
    thread t(threadFunction); // don't add () after threadFunction
    t.join(); // waiting for thread finishing
    return 0;
}