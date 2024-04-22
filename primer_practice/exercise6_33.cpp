/** 编写一个递归函数，输出vector对象的内容。使用alias，iterator */
#include <iostream>
#include <vector>
using namespace std;
using Iter = vector<int>::const_iterator;

void print(Iter first, Iter last) {
    if (first == last) {
        cout << "meet the end" << endl;
        return;
    }
    cout << *first << " ";
    // pass first + 1 should be OK too
    print(first + 1, last);

    // print(++first, last);  // noting using ++first. if using first++, always 1.
    // never meet the end. Also it is not reference, so we will never change first val
}

int main() {
    vector<int> v = {1,2,3,4,5,6,6}; // using initializer_list to initialize vector
    // noting we use cbegin for const iterator
    print(v.cbegin(), v.cend());
    return 0;
}