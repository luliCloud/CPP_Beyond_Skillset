#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        cout << "Please type a number between 0 - 9";
        int num;
        while (cin >> num) {
            if (num > 9) {
                throw runtime_error("A standard input error occured");
            }
        }
        cout << "This message will not be displayed" << endl;
    } catch (runtime_error& e) { // deal with specific error
        cout << "Caught a runtime error: " << e.what() << endl;
    } catch (...) {
        cout << "Caught an exepected exception" << endl;
    }
    cout << "Continue normal execution" << endl;
    return 0;
}
/*
Please type a number between 0 - 9
1
9
0
10
Caught a runtime error: A standard input error occured
Continue normal execution
*/