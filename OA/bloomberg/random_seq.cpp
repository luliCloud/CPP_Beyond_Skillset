#include <iostream>
#include <time.h>  // not sure which function is rand
#include <unordered_map>
#include <vector>
using namespace std;

class StringPermute {
public:
    StringPermute(const string& ori_str) {
        permute_str = ori_str;
        int size = ori_str.size();
        for (int i = 0; i < size; i++) {
            mp[i] = ori_str[i];
        }
    }

    string permute_string() {
        string res = "";
        srand(time(NULL));
        int n = permute_str.size();
        vector<bool> used(n, false); // whether c in this idx is used

        for (int i = 0; i < n; i++) {
            // logic here: we ran the random function to generate a num
            // obtain the mod: num % n. if the number in used is false,
            // indicate the char in this idx has not been used. then we can
            // use it and add to the existing res.
            int num = rand() % n;
            while (used[num]) {
                num = rand() % n;
            }
            used[num] = true;
            res += mp[num];
        }
        return res;
    }

private:
    string permute_str;
    unordered_map<int, char> mp; // idx->char. store original idx of char
};

int main() {
    string str1("achg");
    StringPermute sp(str1);
    string res1 = sp.permute_string();
    cout << res1 << endl;

    string str2("");
    StringPermute sp2(str2);
    string res2 = sp2.permute_string();
    cout << res2 << endl;

    string str3("I am a tree!");
    StringPermute sp3(str3);
    string res3 = sp3.permute_string();
    cout << res3 << endl;
    return 0;
}