#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/** The task is to overload the << operator for Person class in such a way that for 
 * p being an instance of class Person  */
class Person {
public:
    Person(const string& first, const string& last) : 
    firstName(first), lastName(last) {}
    
    const string getFirst() const { return firstName; } 
    const string getLast() const {return lastName;}
    
private:
    string firstName, lastName;
};

/* overloading */
ostream& operator<<(ostream& os, const Person& p) {
    // << is to input all string into os obj
    os << "first_name=" << p.getFirst() << ",last_name=" << p.getLast();
    return os;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string first, last, e;
    cin >> first >> last >> e;
    Person p(first, last);
    
    // not using << and p as the funciton input. but << represent input p info into cout.
    // thus the input para of overloading operator is cout and p. all p info is stored in cout
    cout << p << " " << e << endl;
    return 0;
}