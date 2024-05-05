#include <iostream>
#include <vector>

using namespace std;

/* insert a value*2 in the vector. The insertion condition: value == ele.val
using iterator to find the val */
void insertVector(vector<int>& v, int someValue) {
    auto iter = v.begin(); 
    int mid = v.size() / 2;
    int count = 0;
    while (count <= mid) {
        if (*iter == someValue) {
            iter = v.insert(iter, 2 * someValue); // iter point to 2*someV
            // which is one idx before original iter
            iter++;  // iter go back orignal iter po (but idx++, as whole v.size++)
        }
        iter++;  // move to next ele, as this ele already compared
        count++;
    }
}

int main() {
    vector<int> v{1,2,3,1};
    insertVector(v, 1);
    for (vector<int>::size_type i; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}