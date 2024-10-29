#include <iostream>
#include <utility>
#include <unordered_map>
#include <vector>
using namespace std;

void findEqualSum(const vector<int>& arr) {
    int n = arr.size();
    unordered_map<int, pair<int, int>> mp; // sum->pair<i, j>
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int curr_sum = arr[i] + arr[j];
            if (mp.count(curr_sum)) {
                cout << "Find equal sum for pair 1: " << mp[curr_sum].first << " " << mp[curr_sum].second;
                cout << " pair 2:  " << i << " " << j << " sum: " << curr_sum << endl;
                return;
            } else {
                mp[curr_sum] = {i, j}; // remember this!
            }
        }
    }
    cout << "Cannot find equal sum." << endl;
}   

int main() {
    vector<int> A = {3, 4, 7, 1, 2, 9, 8};
    findEqualSum(A);
    return 0;
}
//Find equal sum for pair 1: 0 6 pair 2:  1 2 sum: 11