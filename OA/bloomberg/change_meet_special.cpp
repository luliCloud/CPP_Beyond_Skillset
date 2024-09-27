#include <iostream>
#include <string>
#include <vector>
using namespace std;

/** 为什么不用for loop。因为我们的起点一定是第一个字母。而不会从后面的字母开始
 * 所以不需要用循环去查看每一个起点的组合
 */

class ChangeSpecial {
public:
    vector<string> res;
    string sub;
    vector<string> chanage_spe(const string& input) {
        backtrack(input, 0);
        return res;
    }

    void backtrack(const string& input, int start) {
        if (start == input.size()) {
            res.push_back(sub);
            return;
        }

        if (input[start] == '0' || input[start] == '1') {
                // remember this!
                sub += input[start];
                backtrack(input, start + 1);
                // 如果不移除，这个字母会一直留在这里。导致变得很长。而且start并不会限制住它
                sub.pop_back();
        } else {
            for (int j = 0; j < 2; j++) {
                char c = '0' + j;
                sub += c;
                backtrack(input, start + 1);
                sub.pop_back();
            }
        }
            
    }

    vector<string> change_spe2(string& str) {
        bk(str, 0);
        return res;
    }

    void bk(string& str, int i) {
        if (i == str.size()) {
            res.push_back(str);
            return;
        }

        if (str[i] == '?') {
            str[i] = '0';
            bk(str, i + 1);

            str[i] = '1';
            bk(str, i + 1);

            str[i] = '?'; // change back
        } else {
            bk(str, i + 1);
        }
    }
};

int main() {
    ChangeSpecial cs;
    string st = "?0?";
    vector<string> res = cs.change_spe2(st);
    for (const auto& r : res) {
        cout << r << " ";
    } 
    cout << endl;
    return 0;
}