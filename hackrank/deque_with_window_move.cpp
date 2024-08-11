#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;
/**
 * Given a set of arrays of size  and an integer , you have to find the 
 * maximum integer for each and every contiguous subarray of size  for each of the 
 * given arrays.

Input Format
First line of input will contain the number of test cases T. For each test case, 
you will be given the size of array N and the size of subarray to be used K. 
This will be followed by the elements of the array Ai.


 * 
 * Double ended queue or Deque(part of C++ STL) are sequence containers with dynamic 
 * sizes that can be expanded or contracted on both ends 
 * (either its front or its back). The member functions of deque that are mainly used are:
 */
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int arrN;
    cin >> arrN;
    
    while (arrN--) {
        int size, window;
        cin >> size >> window;
        
        vector<int> arr(size, 0);
        deque<int> dq;
        vector<int> res;
        
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        for (int i = 0; i < size; i++) {
            int num = arr[i];
            while (!dq.empty() && num > dq.back()) {
                dq.pop_back();  // noting the limit cond must write in while () but not within body.
                // otherwise may never ending the while loop. like if num < back, then always not pop back
            }
            dq.push_back(num);
            
            if (i < window - 1) {
                continue;
            }
            
            res.push_back(dq.front());
            
            if (i >= window - 1 && dq.front() == arr[i - window + 1]) {
                dq.pop_front();
            }
        }
    
        for (int i = 0; i < res.size(); i++) {
            cout << res[i];
            if (i != res.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}