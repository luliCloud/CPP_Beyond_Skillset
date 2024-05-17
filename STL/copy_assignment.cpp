#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class PathName{
	string Name;
public: 
	explicit PathName(const string&) { cout << "constructor" << endl; }
	~PathName() {}
};

class PathName2{
	string Name;
public: 
	PathName2(const string&) { cout << "constructor" << endl; }
	~PathName2() {}
};

int main() {
    string abc("abc");
    PathName xyz(abc);// explicit
    xyz = PathName(abc); 
    cout << "finish" << endl;

    string abc2("abc");
    PathName2 xyz2(abc2);// explicit
    xyz2 = abc2; 
    cout << "finish2" << endl;
    return 0;
}
/**
 * constructor
constructor
finish
constructor
constructor
finish2
*/
