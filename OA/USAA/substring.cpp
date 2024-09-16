#include <iostream>
#include <string>
#include <vector>
using namespace std;

// general way
int find_allsubstr(const string& comstr, const string& substr) {
    int m = comstr.size(), n = substr.size();
    if (n > m) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < m; i++) {
        // find whether match for the string
        int p1 = i, p2 = 0;
        bool found = true;
        for (; p2 < n; p1++, p2++) {
            if (comstr[p1] != substr[p2]) {
                found = false;
                break;
            }
        }
        if (found) {
            count++;
        }
    }
    return count;
}

int KMP(const string& comstr, const string& substr) {
    int m = comstr.size(), n = substr.size();
    if (m < n) {
        return 0;
    }

    // establish the tracing vector for substr
    vector<vector<int>> memo(n, vector<int>(256, 0));
    unsigned char ch = substr[0];
    memo[0][ch] = 1; // noting maybe upper
    int X = 0; // noting the initialize
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 256; j++) {
            memo[i][j] = memo[X][j];
        }
        ch = substr[i];
        memo[i][ch] = i + 1; // step to the next one
        X = memo[X][ch]; // update the X if the X also need move in this ch case
    }

    // check all subseq in comstr 
    int idx = 0;
    int count = 0;
    while (idx < m) {
        int j = 0;
        bool found = false;
        for (int i = idx; i < m; i++) {
            ch = comstr[i];
            j = memo[j][ch];
            if (j == n) {
                count++;
                found = true;
                idx = i;
                break;
            }
        }
        idx++;
    }
    return count;
}

int main () {
    string comstr("Iamppam"), substr("am");
    int res = find_allsubstr(comstr, substr);
    cout << res << endl;

    int res2 = KMP(comstr, substr);
    cout << res2 << endl;
    return 0;
}