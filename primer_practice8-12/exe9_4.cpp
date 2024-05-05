#include <iostream>
#include <vector>
using namespace std;

bool find(vector<int>::iterator begin, vector<int>::iterator end, int i) {
    while (begin != end) {
        if (*begin == i) {
            return true;
        }
        begin++;
    }
    return false;
}

int main() {
    vector<int> v = {1,2,3,4,5};
    cout << find(v.begin(), v.end(), 1) <<  " " 
    << find(v.begin(), v.end(), 10) << endl;

    return 1;
}
/*
output
1 (true)
0 (false)
*/