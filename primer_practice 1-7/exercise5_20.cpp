#include <iostream>
#include <string>
using namespace std;
/*编写一段程序，从标准输入中读取string对象的序列直到连续出现两个相同的单词或者所有的单词都读完为止。使用while循环一次读取一个单词，当一个单词连续出现两次时使用
break语句终止循环。输出连续重复出现的单词，或者输出一个消息说明没有任何单词是连续重复出现的。**/
int main() {
    string read, tmp;
    while (cin >> read) {
        if (read == tmp) {
            break;
        } else {
            tmp = read;
        }
    }
    if (cin.eof()) { // no break but meet ctrl + D
        cout << "no word is repeated." << endl;
    } else {
        cout << read << " occurs twice in succession." << endl;
    }
    return 0;
}