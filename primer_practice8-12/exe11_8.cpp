/**
 * 编写一个程序，在一个已有的vector中搜索，而不是一个set中，保存不重复的单词到新的vector。
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    vector<string> dict{"aa", "bb", "cc"};
    vector<string> vec;
    for (string word; cout << "Enter plz: ", cin >> word; ) {
        bool is_found = binary_search(dict.cbegin(), dict.cend(), word);
        if (!is_found) {
            vec.push_back(word);
        }
    }
    for (auto& w : vec) {
        cout << w << " ";
    }
    cout << endl;
    return 0;
}
/**
Enter plz: lu
Enter plz: an
Enter plz: aa
Enter plz: bb
Enter plz: cc
Enter plz: lu an 
*/