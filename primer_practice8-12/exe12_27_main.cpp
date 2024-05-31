#include "exe12_27.h"
#include <iostream>
#include <fstream>

using namespace std;

void runQueries(ifstream& ifs) {
    TextQuery tq(ifs);
    while (true) {
        cout << "enter word to loof for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl; // print is defined as a global function
    }
}

int main() {
    ifstream ifs("exe12_27.txt");
    runQueries(ifs);
    return 0;
}
/**
 * she occurs2 times
        (line 8)she tells him, at the same time wanting 
        (line 10)Shyly, she asks, "I mean, Daddy, is there?"

enter word to loof for, or q to quit: q
*/