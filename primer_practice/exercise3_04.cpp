#include <iostream>
#include <string>
using namespace std;

/* 编写一段程序读取两个字符串(not sentence)，比较其是否相等并输出结果。
如果不相等，输出比较大的那个字符串。 */
void readTwoStr() {
    string s1, s2;
    while (cin >> s1 >> s2) {  // use ctrl + D to trigger EOF
        if (s1 == s2) {
            cout << "The two strings are equal" << endl;
        } else {
            cout << "The larger string is: " << ((s1 > s2) ? s1 : s2) << endl;
        }
    }
}

/* 比较输入的两个字符串是否等长，如果不等长，输出长度较大的那个字符串。*/
void readTwoLen() {
    string s1, s2;
    while (cin >> s1 >> s2) {  // use ctrl + D to trigger EOF
        if (s1.size() == s2.size()) {
            cout << "The size of two strings are equal" << endl;
        } else {
            cout << "The longer string is: " << ((s1.size() > s2.size()) ? s1 : s2) << endl;
        }
    }
}

int main() {
    //readTwoStr();
    readTwoLen();
    return 0;
}