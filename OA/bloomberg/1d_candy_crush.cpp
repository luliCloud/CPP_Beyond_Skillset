#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
using namespace std;

string candy_crush(const string& s) {
    string res;
    stack<pair<char, int>> st; // {char, count}

    for (char c : s) {
        if (st.empty()) {
            st.push({c, 1});
        } else if (c == st.top().first) {
            st.top().second++;
        } else if (c != st.top().first) {
            if (st.top().second >= 3) {
                st.pop();
            }
            if (st.empty() || c != st.top().first) {
                st.push({c, 1});
            } else {
                st.top().second++;
            } 
        }
    }

    if (!st.empty() && st.top().second >= 3) {
        st.pop();
    }

    while (!st.empty()) {
        char c = st.top().first;
        int cnt = st.top().second;
        st.pop();
        for (int i = 0; i < cnt; i++) {
            res += c;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    string s1 = "aabbccddeeedcba";
    string res1 = candy_crush(s1);
    cout << res1 << endl;

    string s2 = "aabbbacd";
    string res2 = candy_crush(s2);
    cout << res2 << endl;

    string s3 = "aaabbbacd";
    string res3 = candy_crush(s3);
    cout << res3 << endl;

    return 0;
}