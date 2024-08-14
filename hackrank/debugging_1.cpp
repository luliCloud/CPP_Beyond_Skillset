#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void largest_proper_divisor(int n) {
    if (n == 0) {
        throw invalid_argument(to_string(n));  // noting must use throw, but not 
        // invalid_arg then return. throw will auto exit program too
    }
    if (n == 1) {
        throw invalid_argument(to_string(n));
    }
    int res = -1;
    for (int i = n / 2; i >=1; i--) {
        if (n % i == 0) {
            res = i;
            break;
        }
    }
    cout << "result=" << res << endl;
}

void process_input(int n) {
    try {
    largest_proper_divisor(n);
    } catch (invalid_argument& arg) {
        cout << "largest proper divisor is not defined for n=" << arg.what() << endl;
    }
    
    cout << "returning control flow to caller" << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    process_input(n);
     
    return 0;
}