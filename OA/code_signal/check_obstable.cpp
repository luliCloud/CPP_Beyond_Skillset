#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

string findObstable(vector<vector<int>>& operations) {
    string res = "";
    set<int> obs;
    for (const auto& op : operations) {
        if (op[0] == 1) {
            obs.insert(op[1]);
        } else {
            int num = op[1], size = op[2] - 1;
            int a = num - size, b = num + size;
            
            // using upper bound
            if (obs.count(a) || obs.count(b)) {
                // find the obstable at a, cannot place another
                res += '0';
                continue;
            }
            // use lower bound may be also correct. equal or greater both are correct
            auto it = obs.upper_bound(a);
            // 如果至少有一个obstacle的位置比a大，且obstacle的位置又比b小。那么ab一定至少夹着
            // 一个 obstable
            if (it != obs.end() && *it < b) {
                res += '0';
            } else {
                res += '1';
            }
        }   
    }
    return res;
}

int main() {
    vector<vector<int>> ope = {{1,2}, {1,6}, {2,4,2}, {2,5,2}, {2,1,1}, {2,1,2}};
    string res = findObstable(ope);
    cout << res << endl; // 1010
    return 0;
}