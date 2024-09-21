/* it's a dp, and we will use BFS. we try both *2 and / 3
the basic idea we need to have a queue, {value, step}. vector<int> have all values we got so far. 
we don't need to repeat this value again. once we achieve this value, we will return this corresponding step + 1 as result
the front of the queue, in which step should be alwasy less than later one*/
#include <queue>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

class FindMinStep {
public:
    int find_min_step(int target) {
        queue<pair<int, int>> q;  // {value, step}
        set<int> visited; // all values we have met. We don't need to calculate again
        if (target == 1) {
            return 0;
        }

        // we start from one
        visited.insert(1);
        q.push({1, 0});

        // termination: q is empty, indicate we don't find any solution. return -1
        // we find the target, return step + 1
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int val = p.first;
            int step = p.second;

            if (val * 2 == target) {
                return step + 1;
            }

            // check val * 2 is in visited, if not we push to q and visited
            if (!visited.count(val * 2)) {
                visited.insert(val * 2);
                q.push({val * 2, step + 1});
            }
  // we can add val >= 3 as the pre-condition here, but is not mandatory
  // visited can control the whole iteration not enter infinite search
            if (val / 3 == target) {
                return step + 1;
            }
            if (!visited.count(val / 3)) {
                visited.insert(val / 3);
                q.push({val/3, step + 1});
            }
        }
        return -1;
    }
};

int main() {
    FindMinStep fs;
    int res = fs.find_min_step(3);
    cout << res << endl;
    return 0;
}

/** dry run
 * input: 3 (target)
 * 
 * q {{1, 0}}
 * visited: {1}
 * 
 * 1. q {{2, 1}, {0, 1}}; visited {1, 2, 0}
 * step = 0, val = 1
 * val * 2 = 2, step = 1
 * val / 3 = 0, step = 1
 * 
 * 2. {2, 1}. q : {{0, 1}, {4, 2}}; visited:  {1,2,0,4}
 * val = 2, step = 1
 * val * 2 = 4, step = 2
 * val / 3 = 0 (visited)
 * 
 * 3. {0, 1}.q : {{4, 2}}; visited:  {1,2,0,4}
 * val = 0, step 1
 * 
 * 4. {4, 2}. q : {{8, 3}}; visited:  {1,2,0,4,8}
 * val = 4, step = 2
 * val * 2 = 8, step = 3
 * val / 3 = 1
 * 
 * 5. {8, 3} q : {{16, 4}}; visited:  {1,2,0,4,8, 16}
 * val = 8, step = 3
 * val * 2 = 16, step = 4
 * val / 3 = 2
 * 
 * 6. {16, 4}; q : {{32, 5}, {5, 5}}; visited:  {1,2,0,4,8, 16,32,5}
 * val = 16, step = 4
 * val * 2 = 32, step = 5
 * val / 3 = 5, step 5
 * 
 * 7. {32, 5} q : {{5, 5}, {64, 6}, {10, 6}}; visited:  {1,2,0,4,8, 16,32,5, 64, 10}
 * val = 32, step = 5
 * val * 2 = 64, step = 6
 * val / 3 = 10, step = 6
 * 
 * 8. {5, 5} {32, 5} q : {{64, 6}, {10, 6}}; visited:  {1,2,0,4,8, 16,32,5, 64, 10}
 * val = 5, step = 5
 * val * 2 = 10
 * val / 3 = 1
 * 
 * 9. {64, 6} q : {{10, 6}, {128, 7}, {21, 7}}; visited:  {1,2,0,4,8, 16,32,5, 64, 10, 128, 21}
 * val = 64, step = 6
 * val * 2 = 128, step = 7
 * val / 3 = 21, step = 7 (65 // 3 or 65 / 3 is also 21. not go up)
 * 
 * 10 {10, 6} q {{128, 7}, {21, 7}, {20, 7}}; visited:  {1,2,0,4,8, 16,32,5, 64, 10, 128, 21, 20}
 * val = 10, step = 6
 * val * 2 = 20, step = 7
 * val / 3 = 3, step = 7
 * return 7!
 */