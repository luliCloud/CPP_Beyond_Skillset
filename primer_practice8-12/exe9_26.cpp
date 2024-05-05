#include <iostream>
#include <vector>
#include <list>
#include <array>
using namespace std;

/**定义的ia array，将ia 拷贝到一个vector和一个list中。
 * 是用单迭代器版本的erase从list中删除奇数元素(注意不是奇数index)，从vector中删除偶数元素。*/

/* 指针版本 */
void convertAndErase(const int* arr, size_t N) {
    vector<int> v(arr, arr + N);
    list<int> l(arr, arr + N);

    // erase odd num from v. noting it++ don't written in the for loop conditions
    for (auto it = v.begin(); it != v.end(); ) {
        //printf("%p ", it);
        if (*it & 0x1) {        
            it = v.erase(it);  // it 指向被删除元素的下一个元素。如果是最后一个元素，则指向end
            // printf("%p ", it);
        } else {
            it++;
        }
    }

    // erase even num from l
    for (auto it = l.begin(); it != l.end(); ) {
        //printf("%p ", it);
        if (!(*it & 0x1)) {        
            it = l.erase(it);
            //printf("%p ", it);
        } else {
            it++;
        }
    }

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    for (auto it = l.begin(); it != l.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

/** template edition to pass the array (noting not int[])*/
template<typename T, size_t N> // typename generally with T. 
// size_t is a basic data type. size_type is a member of vector
void convertAndErase2(const array<T, N>& arr) {
    vector<T> v(arr.begin(), arr.end());
    list<T> l(arr.begin(), arr.end());

    for (auto it = v.begin(); it != v.end(); ) {
        if (*it & 0x1) {
            it = v.erase(it);
        } else {
            it++;
        }
    }

    for (auto it = l.begin(); it != l.end(); ) {
        if (!(*it & 0x1)) {
            it = l.erase(it);
        } else {
            it++;
        }
    }

    for (typename vector<T>::size_type i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    for (typename list<T>::iterator it = l.begin(); it != l.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

/** using template and generics to pass the whole arr (not first ele*) to func */
template <typename T, size_t N> 
void converAndErase3(const T (&arr)[N]) { 
    // (&arr)传整个arr的指针，而不是退化成第一个元素的指针（如果只用arr作为func 的实参）
    vector<T> v(arr, arr + N);
    list<T> l(arr, arr + N);

    for (auto it = v.begin(); it != v.end(); ) {
        if (*it & 0x1) {
            it = v.erase(it);
        } else {
            it++;
        }
    }

    for (auto it = l.begin(); it != l.end(); ) {
        if (!(*it & 0x1)) {
            it = l.erase(it);
        } else {
            it++;
        }
    }

    for (typename vector<T>::size_type i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    for (typename list<T>::iterator it = l.begin(); it != l.end(); it++) {
        cout << *it << " ";
    }

}

int main() {
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    convertAndErase(arr, sizeof(arr) / sizeof(arr[0]));
    
    array<int, 11> ay = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    convertAndErase2(ay);

    converAndErase3(arr);
    return 0;
}
/*
0 2 8 
1 1 3 5 13 21 55 89 
*/