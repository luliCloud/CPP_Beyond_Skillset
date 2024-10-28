#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// only promise the top is min or max
template <class Type>
void heapify(vector<Type>& arr, bool minHeap) {
    if (minHeap) {
        make_heap(arr.begin(), arr.end(), greater<Type>());
    } else {
        make_heap(arr.begin(), arr.end());
    }
}

int main() {
    vector<int> arr = {3,1,2,5,2};
    heapify(arr, true);
    cout << "min heap: ";
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;

    vector<int> arr2 = {3,1,2,5,2};
    heapify(arr2, false);
    cout << "max heap: ";
    for (int i : arr2) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
/**
 * min heap: 1 2 2 5 3 
max heap: 5 3 2 1 2 
 */