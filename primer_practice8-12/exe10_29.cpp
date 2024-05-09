#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>  // for inserter
#include <fstream>
using namespace std;
/* 从一个文件中 “exe9_49.txt”读取内容，并存储到一个vec中。使用insertor*/
void readFileToVec(const string& file) {
    ifstream ifs(file);
    if (!ifs) {
        cerr << "fail to open " << file << endl;
    }

    /* copy和istream_iterator 一起使用。这个iterator读取文件中的string，用空白符号分割
    它与ifs这个流绑定通过构造函数istream_iterator<string> in(ifs); 绑定之后就从ifs的起始
    开始读取文件内容。但是它不是先读完将所有文件存到ifs里。而是跟copy函数一起。copy让in读一个stirng，
    存到vec里，然后增加iterator到下一个string，直到遇到EOF。eof在这里是一个哨兵变量，意味着
    文件结束。当in遇到eof等值时，自动结束读取 */
    istream_iterator<string> in(ifs), eof;
    vector<string> vec;
    copy(in, eof, back_inserter(vec));
    for (const string& str : vec) {
        cout << str << " ";
    }
    cout << endl;
}

/* 从standard input中读取数字，直到遇到EOF，然后用sort，再copy到
标准输出流中
在 C++ 中，std::copy 函数配合 std::ostream_iterator 
时的行为是直接将每个元素逐个输出到指定的输出流，
而不是先将所有元素存储在某个缓冲区中然后一次性输出。
ostream_iterator 被设计用来向输出流写入数据，每次通过迭代器写入一个元素，就立刻被
输出到关联的输出流中 （cout）*/
void readFromIstream() {
    istream_iterator<int> in(cin), int_eof;
    vector<int> vec;
    copy(in, int_eof, back_inserter(vec));
    sort(vec.begin(), vec.end());

    // to standard output
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

/* modify readFromIstream, only print non-repeat, using unique_copy*/
void readFromIsUni() {
    istream_iterator<int> in(cin), int_eof;
    vector<int> vec;
    // using unique_copy here
    unique_copy(in, int_eof, back_inserter(vec));
    sort(vec.begin(), vec.end());

    copy(vec.cbegin(), vec.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main() {
    readFileToVec("exe9_49.txt");
    readFromIsUni();
    return 0;
}

/**
 * same as text
 * 8 76 45 3 2 1 2 8  (if readFromIstream)
 * 1 2 2 3 8 8 45 76
 * 
 * 8 8 9 102 38 8 2 1 9 1 (readFromIsUni)
 * 1 1 2 8 8 9 9 38 102 
*/
