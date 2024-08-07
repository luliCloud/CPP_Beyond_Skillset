#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> insert_get(vector<vector<string>>& requests, int slotSize) {
    vector<int> slot(slotSize * 2, 0);
    vector<int> res;
    for (const auto& q : requests) {
        string op = q[0], start = q[1], sz = q[2];
        int start_idx = atoi(start.c_str()), size = atoi(sz.c_str());
        if (op == "store") {
            bool found;
            for (int i = start_idx; i < slotSize; i++) {
                found = false;
                for (int j = 0; j < size; j++) {
                    if (slot[i + j] == 1) {
                        found = true;
                        break;  // not work for this start idx
                    }
                }
                if (!found) {
                    for (int j = 0; j < size; j++) {
                        // dual slot need to be filled
                        slot[(i + j) % (2 * slotSize)] = 1;
                        slot[(i + j + slotSize) % (2 * slotSize)] = 1;
                    }
                    res.push_back(i);
                    break;
                }
            }
            if (found) {  // 最后 都还是找到了有1的，所以一定是没有位置了。只好-1
                res.push_back(-1);
            }
        } else {  // free
            int count = 0;
            for (int i = start_idx; i < start_idx + size; i++) {
                
                if (slot[i] == 1) {
                    count++;
                    slot[i] = 0;
                    slot[(i + slotSize) % (2 * slotSize)] = 0;
                }
            }
            res.push_back(count);
        }
    }
    return res;
}

int main() {
    vector<vector<string>> requests = {
        {"store", "0", "6"},
        {"store", "11", "3"},
        {"free", "0", "3"},
        {"store", "10", "3"},
        {"store", "6", "6"},
    };
    vector<int> res = insert_get(requests, 15);
    for (int i : res) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}