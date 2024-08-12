#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // meeting rooms: 0-base idx
        // two minheap, one store avaible room. sorting by room number
        // one store (end, roomNum). for used room
        // one vector<int>, remember the most room holds meeting
        // one time remember what is the time now

        sort(meetings.begin(), meetings.end()); 
        priority_queue<vector<long long>, vector<vector<long long>>, greater<vector<long long>>> used;  // (endTime, room idx)
        priority_queue<int, vector<int>, greater<int>> available;  // room idx
        
        vector<int> arr(n, 0);
        for (int i = 0; i < n; i++) {
            available.push(i);
        }

        for (const auto& meet : meetings) {
            // res = max(res, used.size());
            long long curr_time = meet[0];  // 注意这里一定要从定义开始就用 long long
            long long dif = meet[1] - meet[0];
            int roomIdx;
            
            while (!used.empty() && curr_time >= used.top()[0]) {  
                // used 已经是 long long 注意 curr-time不要定义成int，这样无法比较
                    // all used and time <= curr_time, can go back to available
                available.push(used.top()[1]);
                used.pop();
            }

            if (available.empty()) { // 这里不用放到available里去，因为这个used 肯定是第一个要被用到的了
                curr_time = used.top()[0];
                roomIdx = used.top()[1];
                used.pop();
        
            } else {
                roomIdx = available.top();
                available.pop();
            }
            
            used.push({curr_time + dif, roomIdx});  
            arr[roomIdx]++;
        }
        int maxNum = 0, res = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] > maxNum) {
                res = i;
                maxNum = arr[i];
            }
        }
        return res;
    }
};
