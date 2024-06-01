/**
 * 编写程序实现文本查询，不要定义类来管理数据。你的程序应该接受一个文件，
 * 并与用户交互来查询单词。使用vector、map 和 set 容器来保存来自文件的数据并生成查询结果。
*/
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

int main() {
    ifstream file("exe12_27.txt");
    vector<string> input;
    map<string, set<decltype(input.size())>> dictionary;
    decltype(input.size()) lineNo{ 0 };

    for (string line; getline(file, line); ++lineNo) {
        input.push_back(line);
        istringstream iss(line);
        for (string text, word; iss >> text; word.clear()) {
            /**
             * remove_copy_if 算法在你给出的情况下确实用于去除标点符号。
             * 具体来说，remove_copy_if 是从输入范围（在这个例子中是字符串 text）中复制元素到目标容器（word），同时排除那些满足特定条件（谓词函数返回 true）的元素。
             * 在这个场景中，使用的谓词函数是 ispunct，它检查字符是否为标点符号。
             * 应该是一个一个字符插入到word，最后仍然形成正序单词，但是去掉了标点
            */
            remove_copy_if(text.begin(), text.end(), back_inserter(word), 
                [](unsigned char c){return ispunct(c);});
            dictionary[word].insert(lineNo);
        }
    }

    while (true) {
        cout << "enter words to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        auto found = dictionary.find(s);
        if (found != dictionary.end()) {
            cout << s << " occurs " << found->second.size() 
            << (found->second.size() > 1 ? " times" : " time") << endl;
            for (auto i : found->second) {
                cout << "\t(line " << i + 1 << ") " << input.at(i) << endl;
            }
        } else {
            cout << s << " occurs 0 time" << endl;
        }
    }
    return 0;
}
/**
 * enter words to look for, or q to quit: hair  // address not recognize hair issue in
 * exe12_27
hair occurs 2 times
        (line 1) Alice Emma has long flowing red hair. 
        (line 3) through her hair, it looks almost alive, 
enter words to look for, or q to quit: q

 * enter words to look for, or q to quit: yes
yes occurs 0 time
enter words to look for, or q to quit: hair.
hair. occurs 0 time
enter words to look for, or q to quit: has
has occurs 1 time
        (line 1) Alice Emma has long flowing red hair. 
enter words to look for, or q to quit: she
she occurs 2 times
        (line 8) she tells him, at the same time wanting 
        (line 10) Shyly, she asks, "I mean, Daddy, is there?"
enter words to look for, or q to quit: there
there occurs 2 times
        (line 7) "Daddy, shush, there is no such thing," 
        (line 10) Shyly, she asks, "I mean, Daddy, is there?"
enter words to look for, or q to quit: q
*/