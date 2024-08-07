#include <iostream>
#include <vector>
using namespace std;

bool isMax(const vector<vector<int>>& matrix, int i, int j) {
    // determine the range
    int m = matrix.size(), n = matrix[0].size();
    int num = matrix[i][j];  // len is the same as num
    int start_row = max(0, i - num), end_row = min(m - 1, i + num);
    int start_col = max(0, j - num), end_col = min(n - 1, j + num);
    // remember to excluded the four corner
    for (int row = start_row; row <= end_row; row++) {
        for (int col = start_col; col <= end_col; col++) {
            // noting here is not start row and end row but original corner
            // ending row may the same line as the number, should not be excluded
            if ((row == i - num || row == i + num) && (col == j - num || col == j + num)) {
                continue;
            }
            if (row == i && col == j) {
                continue;
            }
            int curr = matrix[row][col];
            if (curr >= num) {
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> findMax(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> res; // location of local max
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // skip 0
            if (matrix[i][j] == 0) {  // 必须在这里写。等于自己在函数中会被continue。然后返回对
                continue;
            }
            if (isMax(matrix, i, j)) {
                res.push_back({i, j});
            }
        }
    }
    return res;
}

int main() {
    vector<vector<int>> matrix = {
        {3,0,0,0,0},
        {0,0,1,0,0},
        {0,0,2,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,3,0,0,3}
    };
    vector<vector<int>> res = findMax(matrix);
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[0].size(); j++) {
            cout << res[i][j] <<" ";
        }
        cout << endl;
    }
    return 0;
}