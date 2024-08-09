#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int line, qNum;  // noting appearance of <> & </> is not reverse. </> may appear between <>
    cin >> line >> qNum;
    cin.ignore(); // noting when we need to use get line for next line. then we need to ignore '\'. otherwise cin will 
    // skip blankspace directly.
    vector<string> attr, queries;  // store each line in attr or queries
    
    for (int i = 0; i < line; i++) {
        string curr;
        getline(cin, curr);
        attr.push_back(curr);
    }
    for (int i = 0; i < qNum; i++) {
        string curr;
        getline(cin, curr);
        queries.push_back(curr);
    }
    
    unordered_map<string, string> mp; // specific info->value. liek tag1.tag2.tag3~final -> final. if not count in the mp, then return "Not Found!"
    vector<string> tags;  // store temporarily tags chain, for key in mp
    
    for (auto& str : attr) {
        if (str.substr(0, 2) == "</") {
            tags.pop_back(); // the back is tag1.name, which is only needed by tag1. if we meet the ending of the same level. Like b with a </> then, it will be same level as the c. so we should not have a.b.c, but a.c
            continue;
        }
        // remove '\"' and '>'
        str.erase(remove(str.begin(), str.end(), '\"'), str.end()); // noting is not \. not need to remove 
        str.erase(remove(str.begin(), str.end(), '>'), str.end());  
        // remove will move all non '\"' word to front of str, and return a pointer to the first '\"'. \ is an escape symbol
        
        // begin to read message
        string tag, attribute, value;
        char ch; // for all symbol, like <, =
        istringstream iss(str);
        iss >> ch >> tag >> attribute >> ch >> value; // first round. <tag1 value = value
        
        if (tags.empty()) {
            tags.push_back(tag);
        } else {
            string currTag = tags.back() + '.' + tag; // {tag1, tag1.tag2, tag1.tag2.tag3}. if meet tag4 same level as tag2, then remove all tag with tag2 first. then {tag1, tag1.tag4}
            tags.push_back(currTag);
        }
        
        mp[tags.back() + '~' + attribute] = value;
        // if have other attribute
        while (iss) { // noting the terminating condition
            iss >> attribute >> ch >> value;
            mp[tags.back() + '~' + attribute] = value;
        }
    } 
    
    for (const auto& q : queries) {
        if (mp.count(q)) {
            cout << mp[q] << endl;
        } else {
            cout << "Not Found!" << endl;
        }
    }   
    return 0;
}
