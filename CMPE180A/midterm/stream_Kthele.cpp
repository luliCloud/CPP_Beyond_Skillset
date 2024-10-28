#include <queue>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

class KthSmallestTracker {
public:
    KthSmallestTracker(int k) : k_(k) {}

    // Function to process each new number
    void add(int num) {
        // If the heap has less than k elements, add the number directly
        min_heap.push(num);
        if (min_heap.size() > k_) {
            min_heap.pop();
        }
    }

    // Function to get the current k-th smallest element
    int getKthSmallest() const {
        if (min_heap.size() < k_) {
            throw std::out_of_range("Less than k elements in the stream.");
        }
        return min_heap.top();
    }

private:
    int k_;
    priority_queue<int> min_heap; // bottom from greater to smaller. and top is the kth smallest. all greater already
    //pop out
    //std::priority_queue<int, vector<int>, greater<int>> min_heap;  // Min-heap of size k for kth smallest tracking
};

int main() {
    int num;
    KthSmallestTracker kst(3);
    while (true) {
        cin >> num;
        kst.add(num);

        try {
            cout << "Current k ele is " << kst.getKthSmallest() << endl;
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}