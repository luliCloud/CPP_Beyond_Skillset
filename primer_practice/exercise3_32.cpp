/* now to make  vector be copied. 
this file need to run in terminal if using mac vsstudio
g++ -std=c++17 exercise3_32.cpp 
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<int> v1 = {1,2,3,4,5};
    vector<int> v2 = v1; // deep copy
    decltype(v1) v3(v1); // deep copy
    v2[1] = 0;
    v3[2] = 0;
    for (int i = 0; i < v1.size(); i++) {
        cout << v1[i] << " " << v2[i] <<  " " << v3[i] << endl;
    }
    return 0;
}
/*当你复制一个 std::vector 对象时，所进行的是深拷贝（deep copy）。
这意味着新的 std::vector 对象会完全复制原有 vector 的所有元素，
这些元素会存储在新分配的内存中。
这样做确保了原有 vector 和新 vector 之间的操作互不影响。
output:
1 1 1
2 0 2
3 3 0
4 4 4
5 5 5*/