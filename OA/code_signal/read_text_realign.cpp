#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
using namespace std;

vector<string> readTextRealign(const string& text, int width) {
    // read every word in the vector, noting stop sign is accompanying one word
    string word;
    vector<string> words;
    istringstream iss(text);
    while (iss >> word) {
        words.push_back(word);
    }

    unordered_set<char> st = {'.', '!', '?'};
    vector<string> res;
    
    int ptr = 0, curr_w = 0;
    while (ptr < words.size()) {
        vector<string> sentence;
        while (true) {
            string curr = words[ptr];
            ptr++;  // already move to next word

            int size = curr.size();
            sentence.push_back(curr);
            if (st.count(curr[size - 1])) {
                break;
            }
        }
        
        string str = "* ";
        int curr_w = 1;
        
        for (int i = 0; i < sentence.size(); i++) {
            string curr = sentence[i];
            if (curr.size() + curr_w + 1 <= width) {
                str += " " + curr;
                curr_w += curr.size() + 1;
                if (i == sentence.size() - 1) {
                    int left = width - curr_w;
                    str += string(left, ' ');
                    str += "*";
                    res.push_back(str);
                }
            } else {
                str += string(width - curr_w, ' ');
                str += '*';
                res.push_back(str);
                str = "*" + curr;
                curr_w = str.size() - 1;
                if (i == sentence.size() - 1) {
                    int left = width - curr_w;
                    str += string(left, ' ');
                    str += "*";
                    res.push_back(str);
                }
            }
        }

    }
    return res;
}

int main() {
    string text = "Hi! This is the article you have to format properly. Could you do that for me, please?";
    vector<string> res = readTextRealign(text, 16);
    for (const string& r : res) {
        cout << r << endl;
    }

    return 0;
}