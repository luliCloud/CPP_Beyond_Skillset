#include <iostream>
#include <string>
#include <fstream>
using namespace std;
/*
如果一个字母延伸到中线之上，如d 或 f，则称其有上出头部分（ascender）。
如果一个字母延伸到中线之下，如p或g，则称其有下出头部分（descender）。
编写程序，读入一个单词文件，
输出最长的既不包含上出头部分，也不包含下出头部分的单词。
注意不是找到单词中的subseq，而是一个单词文件中的最长单词
*/

void findLongest(const string& newW, string& curr) {
    string not_in = "dfpg";
    if (newW.find_first_of(not_in) == string::npos) {
        curr = newW.size() > curr.size() ? newW : curr;  // noting add curr before =
    }
}

int main() {
    ifstream ifs("exe9_49.txt");
    if (!ifs) {
        return -1;
    }

    string longest;
    string str;
    while (ifs >> str) {
        findLongest(str, longest);
    }
    cout << longest << endl;
    return 0;
}
