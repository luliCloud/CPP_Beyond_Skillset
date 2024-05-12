#include <iostream>
#include <vector>
#include <list>
#include <algorithm> // find
#include <iterator>
using namespace std;

/**
 * using reverse iterator to print a vector
*/
void reversePrint(const vector<int>& vec) {
    cout << "reverse iterator using reverse it: ";
    /**
     * 注意，crbegin实际指向最后一个元素。而crend实际指向第一个数的前一个位置，就是任何元素都没有
     * 这与真正的end对应，也是没有任何实际元素，只是表示最后一个元素再后一个位置
    */
    for (auto it = vec.crbegin(); it != vec.crend(); it++) {  // noting here still++, 
    // but in reality it reverse back
    // the cr just tell two things, treat the end as begin, it reversely go to end (begin)
        cout << *it << " ";
    }
    cout << endl;
}

/* using general iterator to print a vector */
void reversePrintII(const vector<int>& vec) {
    cout << "reverse iterator using general it: ";
    for (auto it = prev(vec.cend()); it != prev(vec.cbegin()); it--) {
        cout << *it <<  " ";
    }
    cout << endl;
}

/**
 * using find to find the distance of last 0 in a list of int to its begin
*/
void findDistance(const list<int>& ls, int ele) {
    // find the last 0 iter
    auto it = find(ls.crbegin(), ls.crend(), ele);
    cout << "The distance of " << ele << "to the begin of the list is: " 
    /** 这里表示的是从it开始到begin的前一个位置的距离。所以是6.0-》0是间隔5个元素
     * 到前一个位置就是六距离了
    */
    << distance(it, ls.crend()) << endl;
}

/**
 * 给定一个包含10 个元素的vector，将位置3到7之间的元素按逆序拷贝到一个list中。
*/
void copyRange(const vector<int>& vec, int a, int b) {
    list<int> ls;
    cout << "copy the given range: " << a << " " << b << " reversely: ";
    copy(vec.cbegin() + a, vec.cbegin() + b, front_inserter(ls));
    for (int n : ls) {
        cout << n << " ";
    }
    cout << endl;
}

/*使用 list 代替 vector 重新实现10.2.3节中的去除重复单词的程序。 */
void elimDups(list<string>& words) {
    words.sort();
    words.unique();
    for (const auto& w : words) {
        cout << w << " ";
    }
    cout << endl;
}

int main() {
    vector<int> vec = {0,1,2,3,4,0,5};
    reversePrint(vec);
    reversePrintII(vec);
    list<int> ls;
    copy(vec.cbegin(), vec.cend(), inserter(ls, ls.end()));
    findDistance(ls, 0);

    vector<int> vec2 = {1,2,3,4,5,6,7,8,9,10};
    // copy idx 3-7 reversely
    copyRange(vec2, 3, 8);

    list<string> words{"apple", "yes", "apple", "pear", "ban"};
    elimDups(words);

    return 0;
}
/*
reverse iterator using reverse it: 5 0 4 3 2 1 0 
reverse iterator using general it: 5 0 4 3 2 1 0 
The distance of 0to the begin of the list is: 6
copy the given range: 3 8reversely: 8 7 6 5 4 
apple ban pear yes 
8 7 6 5 4*/