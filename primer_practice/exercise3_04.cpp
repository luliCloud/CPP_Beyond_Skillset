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
/*操作符重载：>> 是一个被重载的操作符，用于从 cin 对象读取数据。当用于字符串时，
cin >> str 从标准输入读取一个字符串，直到遇到第一个空白字符（如空格、制表符或换行符）
。这意味着它会跳过任何前导的空白字符，并在第一个后续的空白字符处停止读取。

链式提取：cin >> str1 >> str2 利用了 cin 返回自身引用的特性，使得提取运算符可以被
链式调用。首先，cin >> str1 读取并存储第一个遇到的非空白字符串到 str1，然后 cin 
继续向后读取，cin >> str2 将读取下一个非空白字符串到 str2。*/