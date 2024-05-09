#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>  // for bind method
using namespace std;

/*给定一个string，
使用 bind 和 check_size 在一个 int 的vector 中查找第一个大于string长度的值。*/

/* std::bind 函数用于生成一个新的可调用对象。这个对象通过绑定特定的参数到已有函数上，来改变
函数参数的调用方式。在C++中，bind允许程序员预设某些参数的值，或者改变参数的书序。
bind 的基本用法：接受一个函数或可调用对象作为第一个参数，然后是该函数所需的参数列表。使用
placehoders：：_1, _2. 可以在调用时动态的地宫这些参数。*/

/*define checkSize function*/
bool checkSize(const string& str, size_t i) {
    return str.size() < i;
}

void elimdups(vector<string>& vec) {
    stable_sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

/* define checkSize2 for elimdup */
bool checkSize2(const string& str, size_t i) {
    return str.size() >= i;  // find all bigger and put in front
}

/*  */
void biggiest(vector<string>& vec, size_t sz) { 
    elimdups(vec);
    auto it = stable_partition(vec.begin(), vec.end(), 
            bind(checkSize2, placeholders::_1, sz));
    for (auto pos = vec.cbegin(); pos != it; pos++) {
        cout << *pos << " ";
    }
    cout << endl;
}

int main() {
    vector<int> vec{1,2,3,4,5,6,7};
    string str = "abcde";

    // noting put placehoders before _1
    auto it = find_if(vec.cbegin(), vec.cend(), bind(checkSize, str, placeholders::_1));
    if (it != vec.end()) {
        cout << *it << endl;
    }

    vector<string> v = {"the", "quick", "red", "fox", "jumps",
		"over", "the", "slow", "red", "turtle"};
    biggiest(v, 4);

    return 0;
}
/*
6
jumps over quick slow turtle 
*/