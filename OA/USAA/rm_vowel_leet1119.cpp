#include <string>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    string removeVowels(string s) {
        string res = "";
        int n = s.size();
        unordered_set<char> st;
        st.insert('a');
        st.insert('e');
        st.insert('i');
        st.insert('o');
        st.insert('u');

        for (int i = 0; i < n; i++) {
            if (st.count(s[i])) {
                continue;
            }
            res += s[i];
        }
        return res;
    }
};

int main() {
    Solution s1;
    string res = s1.removeVowels("leetcodeisacommunityforcoders");
    cout << res << endl; //"ltcdscmmntyfrcdrs"
    return 0;
}