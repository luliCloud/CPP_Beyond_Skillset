#include <iostream>
#include <string>
#include <vector>
#include "exercise7_person.h"
using namespace std;

int main() {
    Person p1(cin);
    Person p2("Jim", "clara");

    cout << "address: " << p1.getAddress() << " " << p2.getAddress();
    cout << "\nname: " << p1.getName() << " " << p2.getName();
    cout << endl;
    print(cout, p1);
    cout << endl;
    print(cout, p2);
    cout << "\nPlease change p1: ";
    read(cin, p1);
    print(cout, p1);

    return 0;
    /*
    output:
./a.out
uu ii
address: ii clara
name: uu Jim
Person:print() : uu ii
Person:print() : Jim clara
Please change p1: hu sdf
Person:print() : hu sdf*/
}