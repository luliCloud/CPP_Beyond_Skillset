/* 从cin中读取不同person的information */
#include <iostream>  // cin, cout
#include <sstream>  // read string info
#include <fstream> // read file content
#include <string> 
#include <vector>
using namespace std;

struct PersonInfo {
    // struct auto define field members as public
    string name;
    vector<string> phones;
};

int main() {
    string line, word;
    vector<PersonInfo> people;
    istringstream record;

    while (getline(cin, line)) {
        PersonInfo p;
        record.clear(); // clear prev info if have
        record.str(line); // input line content into curr iss. .str() is a member func of iss
        record >> p.name;  // first word input (blank space isolate)
        while (record >> word) {
            p.phones.push_back(word);
        }
        // finish the info of this p, represented by line
        people.push_back(p);
    }

    for (const auto& p : people) {
        cout << p.name << ": ";
        for (const auto& pph : p.phones) {
            cout << pph << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ ./a.out
lu 787 hh 909 202
jinfeng 888 kkk 111
an 888sss 000 999   // ctrl + D
lu: 787 hh 909 202 
jinfeng: 888 kkk 111 
an: 888sss 000 999 
*/