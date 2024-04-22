/* 使用迭代器（iterator）输出一段text的第一段。如果是小写字母全部改为大写 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    vector<string> txt;
    txt.push_back("aaaa Aaaa aaa");
    txt.push_back("");
    txt.push_back("bb bbb bbBb");

    // noting use it->empty() to determine empty
    // if we meet the second ele in txt, which is an "", terminate the loop
    for (auto it = txt.begin(); it != txt.end() && !it->empty(); it++) {
        for (auto &c : *it) {  // noting how to obtain the reference
            if (isalpha(c)) {
                c = toupper(c);  // noting here
            }
        }
    }

    for (auto s : txt) {
        cout << s << endl;
    }

    return 0;
}
/* output
AAAA AAAA AAA

bb bbb bbBb
*/