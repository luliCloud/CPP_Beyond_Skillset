#include <iostream>
#include <string>

using namespace std;
/*接受三个string参数是s、oldVal 和newVal。使用迭代器及insert和erase函数将
s中所有oldVal替换为newVal。测试你的程序，用它替换通用的简写形式，
如，将"tho"替换为"though",将"thru"替换为"through"。
*/

/* using iterator, insert and erase */
void replace(string& s, const string& oldS, const string& newS) {
    auto it = s.begin();
    while (it != s.end() - oldS.size()) { // 如果距离小于oldS，那么不可能有词等于oldS
        if (oldS == string(it, it + oldS.size())) { // 用iterator转换oldS的
        // 一部分为一个string
            it = s.erase(it, it + oldS.size());
            it = s.insert(it, newS.cbegin(), newS.cend());
            it = it + newS.size(); // cannot use it += size, as iterator cannot 
            // accept combine of two operations
        } else {
            it++;
        }
    }
}

/* 这次使用一个下标和replace。 */
void replace2(string& s, const string& oldS, const string& newS) {
    for (size_t i = 0; i < s.size() - oldS.size(); ) {
        if (s.substr(i, oldS.size()) == oldS) {
            s.replace(i, oldS.size(), newS);
            i = i + newS.size();
        } else {
            i++;
        }
    }
}

int main() {
    string s = "to drive straight thru is a foolish, tho courageous act.";
    replace(s, "tho", "though");
    cout << s << endl;
    replace(s, "thru", "through");
    cout << s << endl;

    string s1 = "to drive straight thru is a foolish, tho courageous act.";
    replace2(s1, "tho", "though");
    cout << s1 << endl;
    replace2(s1, "thru", "through");
    cout << s1 << endl;
    return 0;
}
/*
to drive straight thru is a foolish, though courageous act.
to drive straight through is a foolish, though courageous act.*/