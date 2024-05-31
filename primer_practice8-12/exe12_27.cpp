#include "exe12_27.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

TextQuery::TextQuery(ifstream& ifs) : file(new vector<string>) { // file is a shared_ptr
    string text;
    while (getline(ifs, text)) {
        file->push_back(text);
        int n = file->size() - 1;  // 第几行
        istringstream iss(text);
        string word;
        while (iss >> word) {
            // 找到这个单词在map中对应的set，然后插入该行数。auto& 直接接管该shared ptr而不是copy
            /**
             * 内存和性能：
使用 auto line = wm[word]; 会造成一次额外的 shared_ptr 复制，这意味着增加了引用计数和随后减少引用计数的开销。
使用 auto& line = wm[word]; 避免了复制，减少了内存和计算开销，因此在性能敏感的环境中更为合适。
安全性和可读性：
使用 auto& line = wm[word]; 需要确保 wm 在 line 使用期间不被销毁，否则 line 会变成悬空引用。
使用 auto line = wm[word]; 更安全，因为即使原 map 被销毁或修改，line 仍然保持有效。但这会以性能和内存使用为代价。
            */
            auto& lines = wm[word];
            if (!lines) { // lines == nullptr
                lines.reset(new set<line_no>);
            }
            lines->insert(n); // insert the line number of this word
        }
    }
}
/** query a word and return the related query result, including set and complete files */
QueryResult TextQuery::query(const string& s) const {
    /**
     * nodata 是一个指向空 set<line_no> 的 shared_ptr。通过将其定义为 static，
     * 该 shared_ptr 和它指向的 set 在第一次函数调用时被初始化，并在程序的剩余执行期间保持其实例不变。
     * 使用 static 可以确保即使多次调用 query 函数，nodata 指向的 set 只被创建和初始化一次。
     * 这样做减少了内存分配和构造函数调用的开销，特别是当 query 被频繁调用且经常查询不存在的字符串时。
     * 每次查询一个不存在的字符串如果都创建一个新的空 set 和 shared_ptr 将是资源浪费。
    */
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(s);
    if (loc == wm.end()) {
        return QueryResult(s, nodata, file);
    } else {
        return QueryResult(s, loc->second, file);  // directly pass file to QueryResult
    }
}
/* print the freq and corresponding contents of each word */
ostream& print(ostream& os, const QueryResult& qr) {
    // print which line the word appears and frequency
    os << qr.sought << " occurs " << qr.lines->size() << " " << "time"
    << (qr.lines->size() > 1 ? "s" : "") << endl;
    // file is the vector<string>, num is the line word at (start from 1, so num + 1)
    // but when we get the text content in file, we still need the 0th idx, so num
    for (auto num : *qr.lines) {
        os << "\t(line " << num + 1 << ")" << *(qr.files->begin() + num) << endl;
    }
    return os;
}