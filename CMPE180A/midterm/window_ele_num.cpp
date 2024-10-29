#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> uniqueEleNum(const vector<int>& arr, int k) {
    unordered_map<int, int> mp; // ele->freq in fix size window
    vector<int> res;
    if (k > arr.size()) {
        k = arr.size();
    } 

    for (int i = 0; i < k; i++) {
        mp[arr[i]]++; // initialize mp with the first k ele
    }

    res.push_back(mp.size());

    for (int i = k; i < arr.size(); i++) {
        mp[arr[i]]++;
        mp[arr[i -k]]--;
        if (mp[arr[i - k]] == 0) {
            mp.erase(arr[i-k]);
        }
        res.push_back(mp.size());
    }
    return res;
}

int main() {
    vector<int> arr = {1, 2, 1, 3, 4, 2, 3}; // 3 4 4 3
    int k = 4;
    vector<int> res = uniqueEleNum(arr, k);
    for (int r : res) {
        cout << r << " ";
    }
    cout << endl;
    return 0;
}