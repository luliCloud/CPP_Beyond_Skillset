#include <iostream>
#include <vector>
#include <cmath>
#include <climits> // for pow?
using namespace std;

class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        // backpack problem
        // we want to know for each dice, sum from 1 to target. how many combination it can have, if we consider every possible toll
        vector<vector<int>> memo(n + 1, vector<int>(target + 1, 0));
        memo[0][0] = 1; // for sum is 0, no dice, 1 solution found
        long long mod = 1000000007;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                int ans = 0; // calcualte for each num of dices, the possible numof solution to get the subtarget
                for (int l = 1; l <= k; l++) { // obtain the possibilites of every toll val
                    // noting j is curr sum, l should less than curr, otherwise impossible for minus to neg num
                    if (l <= j) {
                        ans = ((ans % mod) + (memo[i - 1][j - l] % mod)) % mod;
                    }
                }

                memo[i][j] = (ans % mod);
            }
        }
        return memo[n][target];
    }
};

int main() {
    int n, k, target;
    cin >> n >> k >> target;
    Solution s;
    int res = s.numRollsToTarget(n, k, target);
    cout << res << endl;
    return 0;
}