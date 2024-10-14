/** 问题 找到一个 index i < j 并且 nums【i】 < nums[j] */
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

vector<int> find_index_pair(const vector<int>& nums) {
    int max_seen = INT_MIN, seen_idx;
    vector<int> res;

    int n = nums.size();
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] > max_seen) {
            max_seen = nums[i];
            seen_idx = i;
        } else if (nums[i] < max_seen) {
            return {i, seen_idx};
        }
    }
    return {-1, -1};
}

int main() {
    vector<int> nums = {3, 1, 2, 5};
    vector<int> res = find_index_pair(nums);
    for (int n : res) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}