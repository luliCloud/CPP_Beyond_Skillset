#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec{0,7,3,2,1,4,5,6};
    nth_element(vec.begin(), vec.begin() + 3, vec.end());
    for_each(vec.begin(), vec.end(), [](int x) {cout << x << " ";});

    return 0;
}
/**
 * 2 0 1 3 4 6 5 7  // 3th position is the n_th ele
*/
