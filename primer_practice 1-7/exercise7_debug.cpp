#include <iostream>
using namespace std;

class Debug {
public:
    Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
    Debug(bool b = false) : hw(b), io(b), other(b) {} // noting all use b value
    // inidcate we can calculate the res when compile, not running. must have a return
    constexpr bool any() const {return hw || io || other; }

    void set_hw(bool b) { hw = b; }
    void set_io(bool b) { io = b; }
    void set_other(bool b) { other = b; }

private:
    bool hw; // runtime error
    bool io; // I/O error
    bool other; // others
};

int main() {
    Debug status;
    status.set_hw(true);
    if (status.any()) { // default is false
        cout << "There is a bug in our system" << endl;
    }
    return 0;
}
/**
 output
 (base) Lis-MacBook-Pro:primer_practice lilv$ g++ -std=c++2b exercise7_debug.cpp 
(base) Lis-MacBook-Pro:primer_practice lilv$ ./a.out
There is a bug in our system
*/