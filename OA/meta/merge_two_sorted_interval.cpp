#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

vector<pair<int, int>> mergeNonOverlapInterval(vector<pair<int, int>>& a, vector<pair<int, int>>& b) {
    int start = INT_MIN, end = INT_MIN;
    vector<pair<int, int>> res;
    int j = 0, i = 0;
    pair<int, int> curr;

    while (i < a.size() || j < b.size()) {
        if (i >= a.size()) {
            curr = b[j];
            j++;
        } else if (j >= b.size()) {
            curr = a[i];
            i++;
        } else {
            if (a[i].first < b[j].first) {
                curr = a[i];
                i++;
            } else {
                curr= b[j];
                j++;
            }
        }

        if (curr.first > end) { // indicate last one has finished
            if (end > INT_MIN) { // indicating already find the first pair
                res.push_back({start, end});
            }
            
            start = curr.first;
            end = curr.second;
        } else {
            end = max(curr.second, end); // start is make sure the smaller one
        }
    }
    if (end > INT_MIN) {
        res.push_back({start, end});
    }
    return res;
}

int main() {
    vector<pair<int, int>> A = {{1,5},{10,14}, {16,18}}, B = {{2,6}, {8,10},{11,20}};
    vector<pair<int, int>> res = mergeNonOverlapInterval(A, B);
    for (const auto& p : res) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}