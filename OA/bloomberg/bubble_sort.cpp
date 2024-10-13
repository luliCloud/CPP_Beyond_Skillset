#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 思路就是两层循环。外层从小到n，控制循环的轮数。内层从小到最后，但是每个iterate减小。n - i - 1
// 然后将最大的数从最左移到当前interval的最右去。保证在越来越小的subarr中，总是将最大的数挪到了最右
// 优化，用一个bool标记该轮是否发生了swap。如果没发生。说明没有任何大的数字在小的数字的左边，则全部有序。可以提前结束

void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = false;

    for (int i = 0; i < n - 1; i++) { // noting end at n - 2. j + 1 will cover n-1
        swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

int main() {
    vector<int> arr = {1, 3, 4, 2};
    bubble_sort(arr);
    for (int n : arr) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}