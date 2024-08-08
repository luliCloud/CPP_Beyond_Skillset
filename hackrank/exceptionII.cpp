#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * In this challenge, you are required to handle error messages while working with 
 * small computational server that performs complex calculations.
It has a function that takes 2 large numbers as its input and returns a numeric result. 
Unfortunately, there are various exceptions that may occur during execution.

Complete the code in your editor so that it prints appropriate error messages, 
should anything go wrong. The expected behavior is defined as follows:

If the compute function runs fine with the given arguments, then print the 
result of the function call.

If it fails to allocate the memory that it needs, print Not enough memory (large number).

If any other standard C++ exception occurs, print Exception (A < 0 or B == 0): 
S where S is the exception's error message.

If any non-standard exception occurs, print Other Exception.

Input Format
The first line contains an integer, T, the number of test cases.
Each of the T subsequent lines describes a test case as 2 space-separated integers, 
A and B, respectively.
 */
class Server {
private:
    static int load; // cannot initialize here
public:
    static int complicatedCalculate(long long A, long long B) {
        load++;

        // find A or B error as the standard error
        if (A < 0) {
            throw invalid_argument("A < 0");  // self-define error
        }

        vector<int> vec(A, 0);
        if (B == 0) {
            throw 0;  // other execeptions
        }

        int res = A / B * (-1);
        int ans = vec[B]; // if outof range, throw other exeception
        return res + A - B * ans; 
    }

    static int getLoad() {
        return load;
    }
};
// initialize here with int type. 
int Server::load = 0;

int main() {
    int T;
    cin >> T;

    while (T--) {
        long long A, B;
        cin >> A >> B;

        try {
            cout << Server::complicatedCalculate(A, B) << endl;
        } catch (bad_alloc& error) {
            cout <<  "Not enough memory" << endl;
        } catch (exception& error) {
            cout << "Exception: " << error.what() << endl;
        } catch (...) {
            cout << "Other Exception" << endl;
        }    
    }
    cout << Server::getLoad() << endl;
    return 0;
}