#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>  // to_lower, ispunct
using namespace std;

/**
 * 编写单词计数器，扩展你的程序，忽略大小写和标点。
 * 例如，"example."、"example,"和"Example"应该递增相同的计数器。
*/
void readToMap(unordered_map<string, int>& mp) {
    string word;
    while (cin >> word) {
        for (char& c : word) {
            c = tolower(c);
        }
        // remove_if 把所有标点移到string的后半部分，返回一个指向该部分开头的it
        // 然后erase从it开始到stirng最后全都删除
        word.erase(remove_if(word.begin(), word.end(), 
        [](unsigned char c){
            return ispunct(c);
        }), word.end());
        mp[word]++;
    }
    for (const auto& [key, val] : mp) {
        cout << key << " " << val << endl;
    }
}

int main() {
    unordered_map<string, int> mp;
    readToMap(mp);
    return 0;
}
/*
input:
thu
she
he
thu
vec
vec
jin
output:
jin 1
vec 2
he 1
she 1
thu 2
*/