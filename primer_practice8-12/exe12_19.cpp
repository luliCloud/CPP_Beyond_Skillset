/**
 * 编写程序，逐行读入一个输入文件，
 * 将内容存入一个 StrBlob 中，用一个 StrBlobPtr 打印出 StrBlob 中的每个元素。
*/
#include <iostream>
#include <fstream>
#include <string>
#include "exe12_19.h"
using namespace std;

int main() {
    ifstream ifs("exe12_19.txt");
    if (!ifs) {
        cerr << "Cannot open the file" << endl;
        return 1;
    }

    StrBlob sb;
    string s;
    while (getline(ifs, s)) { // // 从标准输入读取一行文本，而不是读一个一个单词
        sb.push_back(s);
    }    
    for (StrBlobPtr sbp = sb.begin(); sbp != sb.end(); sbp.incr()) {
        cout << sbp.deref() << endl;
    }

    return 0;
}
/**
 * 0-201-78345-X 2 25
0-201-78346-X 1 100
0-201-78346-X 2 99.9
0-201-78346-X 6 89.9
*/