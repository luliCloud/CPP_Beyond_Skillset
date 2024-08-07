#include <iostream>
#include <vector>
using namespace std;
// using swap!!!!

vector<vector<int>> rotateImage(vector<vector<int>> image, int turns) {
    vector<vector<int>> original = image; // for later copy back
    turns %= 4;
    int n = image.size();

    if (turns == 0) {
        return image;
    } else if (turns == 1) {
        // clockwise rotate
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                swap(image[i][j], image[i][n - j - 1]);
            }
        }

        // diagonal flip  upper right to down left
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) { // noting the limitation
            // (0,2) -> (1, 3) ..0-3,0-3
                swap(image[i][j], image[n - 1 - j][n - 1 - i]);
            }
        }

    } else if (turns == 2) {
        // up down, left right. order does not matter
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n / 2; i++) { // row
                swap(image[i][j], image[n - i - 1][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                swap(image[i][j], image[i][n - j - 1]);
            }
        }
    } else {  // turn 3 -> anti-clock
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                swap(image[i][j], image[i][n - j - 1]);
            }
        }
// diagonal upper left to down right
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) { // noting the limitation
            // (0,2) -> (2, 0) ..0-3,0-3
                swap(image[i][j], image[j][i]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || i == n - j - 1) {
                image[i][j] = original[i][j];
            }
        }
    }
    return image;
}

int main() {
    vector<vector<int>> image = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    vector<vector<int>> res1 = rotateImage(image, 1);
    vector<vector<int>> res2 = rotateImage(image, 2);
    vector<vector<int>> res3 = rotateImage(image, 3);

    for (int i = 0; i < res1.size(); i++) {
        for (int j = 0; j < res1.size(); j++) {
            cout << res1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < res1.size(); i++) {
        for (int j = 0; j < res1.size(); j++) {
            cout << res2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < res1.size(); i++) {
        for (int j = 0; j < res1.size(); j++) {
            cout << res3[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}