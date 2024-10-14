#include <vector>
#include <iostream>
using namespace std;

/** maxHeap 是一种特殊的二叉树，两个children的值永远小于parent的值。因此root一定是最大值。底下的排序不一定有序 */
class MaxHeap {
public:
    vector<int> heap;

    // heap down. heapfying down the node at index i. helper function
    void heapifyDown(int i) {
        int largest = i; // suppose the i is the root
        int left = i * 2 + 1, right = i * 2 + 2;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            // indicate largest is not original root, we need to swap and keep heapifyDown
            swap(heap[largest], heap[i]);
            heapifyDown(largest); // the value in current largest is a smaller num, may not meet criteria
        }
    }

    // helper funciton. heapifyUp the node at index i
    void heapifyUp(int i) {
        // compare i and its parent
        int parent = (i - 1) / 2; // noting here!

        if (heap[i] > heap[parent]) {
            swap(heap[i], heap[parent]);
            heapifyUp(parent); // the num at parent now may be not the right one
        }
    }

    // below is the real API we should design for max heap

    // insert a new val to the heap. First insert to the end then heapifyUp
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    // return max value, and pop it
    int extractMax() {
        int n = heap.size();
        if (n == 0) {
            cout << "Heap is empty" << endl;
            return -1;
        }

        int val = heap[0]; // 0 is the root of whole heap
        swap(heap[0], heap[n - 1]);
        heap.pop_back();

        heapifyDown(0);
        return val;
    }

    // get MaxValue
    int getMax() {
        if (heap.size() == 0) {
            cout << "Heap is empty" << endl;
            return -1;
        }

        return heap[0];
    }

    // printHeap
    void printHeap() const {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap mh;
    for (int i = 10; i > 0; i--) {
        mh.insert(i);
        if (i % 4 == 0) {
            mh.extractMax();
        }   
        
        int maxH = mh.getMax();
        cout << maxH << " ";
    }
    cout << endl;
    return 0; 
}