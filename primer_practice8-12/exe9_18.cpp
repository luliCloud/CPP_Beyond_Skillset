#include <iostream>
#include <string>
#include <deque>
using namespace std;

/* read all input from I/O into a deque, using iterator to read and print
all contetns in the deque */
void printDequeFromIO(istream& is) {
    deque<string> input;
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
i am a 
tree
(output)
i am a tree 
*/