/*编写一段程序从标准输入中一次读入一行，然后修改该程序使其一次读入一个词。

一次读入一行
一次读入一个词
*/
#include <iostream>
#include <string>  
using namespace std;

void readLine() {
    /* one line per read*/
    string s;
    cout << "enter a sentence: ";
    // getline meet EOF then return false, otherwise return true
    while (getline(cin, s)) {  // using ctrl + D to trigger EOF
        cout << s << endl;
    }
    std::cout << "Exited loop due to EOF or input error." << std::endl;
}

void readWord() {
    /* one line per word */
    string s;
    cout << "enter a word";
    while (cin >> s) {
        cout << s << endl;
    }
    std::cout << "Exited loop due to EOF or input error." << std::endl;
}

/* 这个文件需要用terminal 手动编译运行。VS不支持debug consle cin 功能 */
int main() {
    readLine();
    // readWord();
    return 0;
}
/*output
readLine():
enter a sentence: i am a y 
i am a y 
Exited loop due to EOF or input error.

readWord():
enter a sentence: i am a y 
i 
am 
a 
y 
Exited loop due to EOF or input error.
*/