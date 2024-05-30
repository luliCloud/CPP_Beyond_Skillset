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

    cout << "为了能让 StrBlobPtr 使用 const StrBlob，你觉得应该如何修改？定义一个名为ConstStrBlobPtr 的类，\
使其能够指向 const StrBlob。构造函数改为接受 const Strblob & , 然后给 Strblob 类添加两个\
const 成员函数 cbegin 和 cend，返回 ConstStrBlobPtr。" << endl;
    const StrBlob csb = sb;   
    for (StrBlobPtr csbp = csb.cbegin(); csbp != sb.end(); csbp.incr()) {
        cout << csbp.deref() << endl;
    }

    return 0;
}
/**
0-201-78346-X 1 100
0-201-78346-X 2 99.9
0-201-78346-X 6 89.9
为了能让 StrBlobPtr 使用 const StrBlob，你觉得应该如何修改？
定义一个名为ConstStrBlobPtr 的类，使其能够指向 const StrBlob。
构造函数改为接受 const Strblob & , 然后给 Strblob 类添加两个const 成员函数 cbegin 和 cend，
返回 ConstStrBlobPtr。
0-201-78345-X 3 20
0-201-78345-X 2 25
0-201-78346-X 1 100
0-201-78346-X 2 99.9
0-201-78346-X 6 89.9
*/