#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

string highestAveScore(vector<string>& records) {
    unordered_map<string, vector<int>> mp; // name->vector(scores)
    // read the records
    for (const string& re : records) {
        int n = re.size();
        int i = 0;
        for (; i < n; i++) {
            if (re[i] == ':') {
                break;
            }
        }
        string name = re.substr(0, i);
        string sc = re.substr(i + 1);  // can skip the space when convert to num
        int score = atoi(sc.c_str()); 
        mp[name].push_back(score);
    }

    priority_queue<pair<string, double>, vector<pair<string, double>>, 
    function<bool(pair<string, double>, pair<string, double>)>> pq(
        [](pair<string, double> a, pair<string, double> b) {
            return a.second < b.second;
        }
    );

    for (const auto& [name, v] : mp) {
        int sum = 0;
        int n = v.size();
        for (int s : v) {
            sum += s;
        }
        double score = (double) sum / n;
        pq.push({name, score});
    }
    return pq.top().first;
}

int main() {
    vector<string> records = {
        "John: 5", "Michael: 4", "Ruby: 2", "Ruby: 5", "Michael: 5"
    };
    string res = highestAveScore(records);
    cout << res << endl;

    vector<string> records2 = {
        "Kate: 5", "Kate: 5", "Maria: 2", "John: 5", "Michael: 4", "John: 4"
    };
    string res2 = highestAveScore(records2);
    cout << res2 << endl;
    return 0;
}