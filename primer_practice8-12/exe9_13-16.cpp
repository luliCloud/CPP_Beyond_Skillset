#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

/* using size_type but not int to iterate vector */ 
void printVector(const vector<int>& v) {
    for (vector<int>::size_type i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

/* assign the char* elements in a list to a vector of string */
vector<string> convertCharStr(const list<const char*>& l) {
    vector<string> vec;
    vec.assign(l.cbegin(), l.cend());
    vector<string> v2(l.cbegin(), l.cend());
    return vec;
}

/* assign the char* elements in a list to a vector of string, method 2 */
vector<string> convertCharStr2(const list<const char*>& l) {
    vector<string> vec(l.cbegin(), l.cend());
    return vec;
}

/** compare a list and a vector content equalling*/
void compareVecList(const vector<string>& v, const list<const char*>& l) {
    vector<string> copyV(l.cbegin(), l.cend());
    cout << (v == copyV ? "equal" : "non-equal") << endl;
}

int main() {
    vector<int> v = {1,2,3,4,5};
    printVector(v);

    list<const char*> l{"hello", "world"};  // noting how to initialize
    vector<string> strs = convertCharStr(l);
    for (const auto& s : strs) {
        cout << s << " ";
    }
    cout << endl;

    vector<string> strs2 = convertCharStr2(l);
    for (const auto& s : strs2) {
        cout << s << " ";
    }
    cout << endl;

    compareVecList(strs, l);

    return 0;
}