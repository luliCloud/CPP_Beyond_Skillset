#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct State {
    int x, y;
    int gas;
    State(int x, int y, int gas) : x(x), y(y), gas(gas) {} 
};

bool reach_oasis(vector<vector<char>> grid, vector<int> oasis, vector<int> car, int gas) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visit(m, vector<bool>(n, false));
    State s1(car[0], car[1], gas);

    queue<State> q;
    q.push(s1);
    vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    // BFS
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        // meet oasis
        if (curr.x == oasis[0] && curr.y == oasis[1]) {
            return true;
        }

        // update visit
        visit[curr.x][curr.y] = true;
        // meet osbtacle, skip
        if (grid[curr.x][curr.y] == '#') {
            continue;
        }

        // if meet gas station, update gas vol
        if (grid[curr.x][curr.y] == 'G') {
            curr.gas += gas;
        }

        // go up, down, left, right to see whether reach oasis, update gas. 
        // check visit
        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dir[i][0], newY = curr.y + dir[i][1], newGas = curr.gas-1;
            if (newX < 0 || newY < 0 || newX >= m || newY >= n) {
                continue;
            }

            if (visit[newX][newY]) {
                continue;
            }

            if (newGas < 0) {
                continue;
            }

            State newS(newX, newY, newGas);
            q.push(newS);
        }
    }
    return false;
}

int main() {
    vector<vector<char>> grid = {
        {'G', '.', 'o', '.'},
        {'.', '#', '.', '.'},
        {'.', '.', '#', '.'},
        {'C', '.', '.', '.'}
    };
    
    int gas = 3;  // 初始汽油量
    if (reach_oasis(grid, {3, 0}, {0, 2}, gas)) {
        cout << "can reach oasis" << endl;
    } else {
        cout << "cannot reach oasis" << endl;
    }
    
    return 0;
}
