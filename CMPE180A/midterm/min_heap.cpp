#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

template <class Type>
class MinHeap {
public:
    void push(Type val) {
        arr.push_back(val);
        int idx = arr.size() - 1;
        heapifyUp(idx);
    }

    void pop() {
        if (arr.size() == 0) { // noting here
            throw runtime_error("Heap is empty!");
        }
        int n = arr.size();
        swap(arr[0], arr[n - 1]);
        arr.pop_back();
        if (!arr.empty()) {
             heapifyDown(0);
        }
    }

    Type peek() {
        if (arr.size() == 0) {
            throw runtime_error("Heap is empty!");
        }
        return arr[0];
    } 

    int size() {
        return arr.size();
    }

private:
    vector<Type> arr;

    // heapUp: compare current idx val with its parent value. if it is smaller than parent, swap. keep up
    void heapifyUp(int idx) {
        if (idx > 0 && arr[idx] < arr[(idx - 1) / 2]) {
            swap(arr[idx], arr[(idx - 1) / 2]);
            heapifyUp((idx - 1) / 2);
        }
    }

    // heapdown: compare current idx val with its left and right children. 
    // swap with minimal children (then the new parent should greater than both down and the other child)
    void heapifyDown(int idx) {
        
        int left_child = idx * 2 + 1;
        int right_child = idx * 2 + 2;
        int n = arr.size();
        if (idx >= n) {
            return;
        }
        
        int minimum = arr[idx]; // this is the idx
        if (left_child < n && minimum > arr[left_child]) {
            minimum = left_child;
        }

        if (right_child < n && minimum > arr[right_child]) {
            minimum = right_child;
        }

        if (minimum != idx) {
            swap(arr[minimum], arr[idx]);
            heapifyDown(minimum);
        }
    }
};

int main() {
    MinHeap<int> mh;
    int arr[5] = {3,1,2,6,0};
    for (int a : arr) {
        mh.push(a);
    }
    cout << mh.peek() << " " << mh.size() << endl;  // 0 5

    mh.pop();
    cout << mh.peek() << " " << mh.size() << endl;  // 1 4
    return 0;
}   