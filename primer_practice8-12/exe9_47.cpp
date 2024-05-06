#include <iostream>
#include <string>
using namespace std;
/*首先查找string"ab2c3d7R4E6"中每个数字字符，然后查找其中每个字母字符。编写两个版本的程序，
第一个要使用find_first_of，第二个要使用find_first_not_of。*/

int main() {
    string str = "ab2c3d7R4E6";
    string numbers = "0123456789";
    for (size_t pos = 0; pos != string::npos; ) {
        pos = str.find_first_of(numbers, pos); // 找到str中第一个出现numbers中包含字符的位置
        // 如果不写一下check，那么即使找到npos也会默认pos++，跳过npos
        if (pos != string::npos) {
            cout << str[pos] << " ";
        // pos 返回该字符所在位置。所以pos在还要再++,注意不能再loop里++，这样会跳过check
            pos++;
        }
        
    }
    cout << endl;

    for (size_t pos = 0; pos != string::npos; ) {
        pos = str.find_first_not_of(numbers, pos); // find ASCII not in numbers
        if (pos != string::npos) {
            cout << str[pos] << " ";
            pos++;
        }
        
    }
    cout << endl;

    return 0;
}