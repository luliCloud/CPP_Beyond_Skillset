#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

vector<int> flipCountOne(vector<string>& requests, const string& str) {
    unordered_map<int, int> mp; // idx->num of 1
    int count = 0;
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c == '1') {
            count++;
            
        }
        mp[i] = count; 
    }

    bool ori = true;
    vector<int> res;
    for (string& req : requests) {
        if (req[0] == 'f') {
            ori = !ori;
        } else {
            // determine the 1 in request i
            string word;
            stringstream ss(req);
            int cnt = 0;
            while (getline(ss, word, ':')) {
                if (cnt == 1) {
                    int idx = atoi(word.c_str());
                    if (ori) {
                        res.push_back(mp[idx]);
                    } else {
                        int n = idx + 1 - mp[idx];
                        res.push_back(n);
                    }
                }
                
                cnt++;
            }
        }
    }
    return res;
}

int main() {
    string str = "0000101";
    vector<string> requests = {
        "count:4", "count:6", "flip", "count:4", "flip", "count:2"
    };
    vector<int> res = flipCountOne(requests, str);
    for (int n : res) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}