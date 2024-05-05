#include <iostream>
#include <string>
#include <deque>
using namespace std;

/* read all input from I/O into a deque, using iterator to read and print
all contetns in the deque */
void printDequeFromIO(istream& is) {
    deque<string> input;
    // list<string> input -> also works, no other changes needed
    string str;
    while (is >> str) {
        input.push_back(str);
    }
    cout << "input is: ";
    for (auto iter = input.cbegin(); iter != input.cend(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
}

int main() {
    printDequeFromIO(cin);

    return 0;
}
/*
yew ia ma
input is: yew ia ma 
*/