#include "pp6.h"
#include <iostream>
#include <algorithm>

string mergeString(const vector<string> &a) {
    int n = a.size();
    string res = "";

    int max_len = 0; // find the max_len in a
    for (const string& sub : a) {
        int sz = sub.size();
        max_len = max(sz, max_len);
    }

    for (int i = 0; i < max_len; i++) {
        // inner loop iterate every string inside a
        for (int j = 0; j < n; j++) {
            if (i < a[j].size()) {
                res += a[j][i];
            }
        }
    }
    return res;
}

// int main() {
//     vector<string> a = {"abc", "e", "defghji"};

//     string res = mergeString(a);
//     cout << res << endl;
//     return 0;
// }