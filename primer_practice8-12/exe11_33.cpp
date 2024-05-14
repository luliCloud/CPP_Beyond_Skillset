#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
using namespace std;
/** 利用 transformer rule 文件创建自己的文件转换程序 */
void word_transform(ifstream&, ifstream&);
map<string, string> buildMap(ifstream&);
string transform(const string&, map<string, string>&);

int main() {
    ifstream ifs_rules("exe11_33_transformer_rules.txt");
    ifstream ifs_txt("exe11_33.txt");

    word_transform(ifs_rules, ifs_txt);
    return 0;
}

void word_transform(ifstream& ifs_rules, ifstream& ifs_txt) {
    auto rule_map = buildMap(ifs_rules);  // transformer rules in a map
    string text;
    while (getline(ifs_txt, text)) {  // read one line from txt
        istringstream iss(text);  // read one word from each line
        string word;
        bool firstWord = true;
        while (iss >> word) {
            if (firstWord) {
                firstWord = false;  // first word no need to cout " "
            } else {
                cout << " ";
            }
            cout << transform(word, rule_map);
        }
        cout << endl;  // one line end
    }
}

map<string, string> buildMap(ifstream& ifs) {
    /**
     * 这段代码严格要求每个键后面必须有有效的非空白字符数据，否则将认为规则文件不完整或格式错误，从而触发异常。
     * 这种方式有助于确保数据的完整性和准确性，防止程序在后续处理中因缺少数据而出错。
    */
    map<string, string> mp;
    string key, word;
    /**
     * key先从ifs读一个词，然后getline读该行剩余的部分。连key后面的空格都读了
    */
    while (ifs >> key && getline(ifs, word)) {
        if (word.size() > 1) {
            mp[key] = word.substr(1); // start from 1, skip first blank space
            /**
             * 当一个转换规则的关键字多次出现的时候，使用下标运算符会保留最后一次添加的规则，
             * 而用insert则保留第一次添加的规则。
            */
           // trans_map.insert({key, value.substr(1)});
        } else {
            throw runtime_error("no rules for key: " + key);
        }
    }
    return mp;
}

string transform(const string& s, map<string, string>& mp) {
    auto it = mp.find(s);
    if (it != mp.end()) {
        return it->second;
    } else {
        return s;
    }
}
/**
 * where are you
why dont you send me a picture
okay? thanks! later
be right back  // even three words are printed out together
*/