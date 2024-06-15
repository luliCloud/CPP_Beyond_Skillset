/**
 * 读写锁： 读写锁允许多个读操作同时进行，但写操作是排他的，这适用于读多写少的场景，可以提高并发性能
 * 实现：可以使用std::shared_mutex(C++17引入)来实现读写锁
 */
#include <shared_mutex> // for unique_lock?
#include <iostream>
#include <vector>
#include <mutex>
using namespace std;

/** 应该是不同的thread可以对vector所有的元素都可以对vector进行读写？ */
class ReadWriteVector {
private:
    mutable shared_mutex rw_mutex_;
    vector<int> vec_;
public:
    void add(int value) {
        // avoid other threads write
        unique_lock<shared_mutex> lock(rw_mutex_);
        vec_.push_back(value);
    }

    int get(int index) const {
        unique_lock<shared_mutex> lock(rw_mutex_);
        return vec_.at(index); // at is similar to [] but can check boundary. avoid out of range
    }

    int size() const {
        unique_lock<shared_mutex> lock(rw_mutex_);
        return vec_.size();
    }
};

int main() {
    ReadWriteVector rwVec;
    rwVec.add(10);
    cout << "Element at index 0: " << rwVec.get(0) << " and size is " << rwVec.size()
    << endl; 

    return 0;
}
