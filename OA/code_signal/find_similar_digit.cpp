#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int count(vector<int>& arr) {
    // mp[i] represents how many times i has been met so far
    unordered_map<int, int> mp;

    int res = 0;
    for (auto& num : arr) {
        // visit each digit for num starting from the least significant bit
        for (long long cursor = 1; cursor <= num; cursor *= 10) {
            int curDigit = (num / cursor) % 10;
            // try to replace the curDigit with a new digit
            for (int newDigit = 0; newDigit <= 9; newDigit++) {
                if (newDigit == curDigit) {
                    continue;
                }
                int newNum = num - (curDigit * cursor) + (newDigit * cursor);
                // for example, if 1234 becomes 0234, it doesn't count
                if (newNum == 0 && num / cursor <= 9) {
                    continue;
                }
                res += mp[newNum];
            }
        }
        mp[num]++;
    }
    return res;
}

int findSimilar(vector<int>& nums) {
    // using string and int to indicate how many times have met before
    // only consider what have met before, not consider there after. 
    unordered_map<string, int> mp; // num->freq have met so far
    int res = 0;
    for (int num : nums) {
        string curr = to_string(num);
        for (int i = 0; i < curr.size(); i++) {
            // replace every digit
            
            for (int j = 0; j < 10; j++) {
                string copied = curr; // remember put here. otherwise below condition is not accurate
                int curr_d = curr[i] - '0';
                if (j == curr_d) {
                    continue;
                }
                copied[i] = j + '0';
                res += mp[copied]; // if not exist, 0, otherwise count the freq
            }
        }
        mp[curr]++; // meet one more time
    }
    return res;
}

int main() {
    vector<int> nums = {1,151,241,1,9,22,351};
    int res = findSimilar(nums);
    cout << res << endl;
    return 0;
}