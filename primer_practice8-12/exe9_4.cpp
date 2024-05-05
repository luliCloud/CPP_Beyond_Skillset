#include <iostream>
#include <vector>
using namespace std;

/** return whether find this val */
bool find(vector<int>::iterator begin, vector<int>::iterator end, int i) {
    while (begin != end) {
        if (*begin == i) {
            return true;
        }
        begin++;
    }
    return false;
}
/** return the iterator of this value. if not exist, return the end*/
vector<int>::iterator findIndex(vector<int>::iterator begin, 
                                vector<int>::iterator end, int i) {
    while (begin != end) {
        if (*begin == i) {
            return begin;
        }
        begin++;
    }
    return end;
}

int main() {
    vector<int> v = {1,2,3,4,5};
    cout << find(v.begin(), v.end(), 1) <<  " " 
    << find(v.begin(), v.end(), 10) << endl;

    cout << *findIndex(v.begin(), v.end(), 4) <<  " " 
    << *findIndex(v.begin(), v.end(), 10) << endl;

    printf("%p\n", v.begin());
    printf("%p\n", (v.begin() + 1));
    printf("%p\n", (v.begin() + 2));
    printf("%p\n", (v.begin() + 3));
    printf("%p\n", (v.begin() + 4));
    printf("%p\n", v.end());
    
    return 0;
}
/*
output
1 (true) 0 (false)
4 0(derefence of v.end())
0x7f7f86705d10
0x7f7f86705d14
0x7f7f86705d18
0x7f7f86705d1c
0x7f7f86705d20
0x7f7f86705d24
*/