#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool isOddZero(int num) {
    string curr = to_string(num);
    int count = 0;
    for (char c : curr) {
        if (c == '0') {
            count++;
        }
    }
    if (count % 2 == 1) {
        // cout << curr << endl;
        return true;
    }
    return false;
}

int oddNumZero(vector<int>& arr) {
    int res = 0;
    for (int num : arr) {
        if (isOddZero(num)) {
            res++;
        }
    }
    return res;
}

int main() {
    vector<int> arr = {4, 50, 100, 65, 2000, 700, 1, 10};
    int res = oddNumZero(arr);
    cout << res << endl;
    return 0;
}