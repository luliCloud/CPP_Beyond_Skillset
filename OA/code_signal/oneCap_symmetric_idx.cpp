#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

long long findAllSymmetricIdx(vector<int>& a, vector<int>& b) {
    unordered_map<int, int> mp; // sum of b[i] + b[i] -> freq
    /** a[i] - b[j] == a[j] - b[i]
     * -> a[i] + b[i] = a[j] + b[j]
     * 所以我们要找到所有从i开始，往后的可以跟i一样和的idx。可以包括i
     * 那么实际上从i开始往后数会有n个，就是 
     * (n + n - 1 + n - 2 ... + 1) -> n(n - 1) / 2, n 为freq of sum
     */
    for (int i = 0; i < a.size(); i++) {
        int sum = a[i] + b[i];
        mp[sum]++;
    }

    long long res = 0;
    for (const auto& [k, v] : mp) {
        res += (v + 1) * v / 2;
    }
    return res;
}

int main() {
    vector<int> a = {1, 2, 3, 4}, b = {2,1,4,3}, a2 = {0,255}, b2={255,0};

    long long res = findAllSymmetricIdx(a, b);
    long long res2 = findAllSymmetricIdx(a2,b2);
    cout << res << " " << res2 << endl;
    return 0;
}