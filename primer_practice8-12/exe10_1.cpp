#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <numeric>  // for accumulate
using namespace std;

/* using count in algorithm lib to count the freq of an int in the vector */
void usingCount(const vector<int>& vec) {
    cout << "Freq of 6 in the vector is: " << count(vec.cbegin(), vec.cend(), 6) << endl;
}

/* count string in a list contariner using count */
void countStringInList(const list<string>& ls) {
    cout << "Freq of aa in the list is: " << count(ls.cbegin(), ls.cend(), "aa") << endl;
}

/* using accumulate to count the sum in a vector */ 
void sumOfVec(const vector<int>& vec) {
    // 0 是累积的初始值
    cout << "Sum of vec is " << accumulate(vec.cbegin(), vec.cend(), 0) << endl;
}

int main() {
    vector<int> vec{1,2,3,5,6,8,2,6,6};
    usingCount(vec);

    list<string> ls{"a", "b", "aa", "aaa", "aa"};
    countStringInList(ls);

    sumOfVec(vec);

    return 0;
}