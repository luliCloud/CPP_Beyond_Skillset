#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void print_interval(const string& str) {
    string res = str;
    sort(res.begin(), res.end());
    int n = res.size();
    for (int i = 0; i < n; i += 2) {
        cout << res[i];
    }
    cout << endl;
}

vector<int> find_interval(vector<int>& arr) {
    vector<int> copy = arr;
    sort(copy.begin(), copy.end());
    for (int i = 0; i < copy.size(); i++) {cout << copy[i];}
    cout << endl;

    vector<int> res;
    int n = copy.size();
    for (int i = 0; i < n; i+=2) {
        res.push_back(copy[i]);
    }
    return res;
}

int main() {
    string str = "I am good";
    print_interval(str);

    string str2 = "mraeu";
    print_interval(str2);

    vector<int> arr = {10, 7, 4, 5, 8};
    vector<int> res = find_interval(arr);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}