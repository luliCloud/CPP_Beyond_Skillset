#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

int main() {
    unordered_map<string, int> myHash;

    cout << "map size=" << myHash.size() << endl;
    string a("juan");
    string b("Carlos");
    pair<string, int> p1(a, a.size());
    pair<string, int> p2= {b, b.size()};
    myHash.insert(p1);
    myHash.insert(p2);

    auto it = myHash.find(a); // return iterator
    if (it == myHash.end()) {
        cout << a << " is not found" << endl;
    } else {
        cout << a << " is found and value is " << (*it).second << endl;
    }
    cout << "size is " << myHash.size() << endl;
    cout << "max load factor " << myHash.max_load_factor() << endl;
    cout << "load factor " << myHash.load_factor() << endl;
    return 0;
}