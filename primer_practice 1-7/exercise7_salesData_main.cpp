#include "exercise7_salesData_own.h"

int main() {
    cout << "1. default way: " << endl;
    cout << "----------------" << endl;
    SalesData s1;
    print(cout, s1);

    cout << "\n2.using std::string as parameter: " << endl;
    cout << "----------------" << endl;
    SalesData s2("CPP-Primer-5th");
    print(cout, s2);

    cout << "\n3. complete parameters: " << endl;
    cout << "----------------" << endl;
    SalesData s3("CPP-Primer-5th", 3, 25.0);
    print(cout, s3);

    cout << "\n4. use istream as parameters: " << endl;
    cout << "----------------" << endl;
    SalesData s4(cin);
    print(cout, s4);

    cout << "\n5. use friend method add to add two SalesData: " << endl;
    cout << "----------------" << endl;
    SalesData s5 = add(s4, s3);
    print(cout, s5);
    cout << endl;
    return 0;
}
/** output 
 * lu 8 86.5(base) Lis-MacBook-Pro:primer_practice lilv$ g++ -std=c++2b -g exercise7_salesData_maercise7_salesData_own.cpp 
(base) Lis-MacBook-Pro:primer_practice lilv$ ./a.out
1. default way: 
----------------
SalesData(const string& s, unsigned n, double p)
SalesData()
 0 0
2.using std::string as parameter: 
----------------
SalesData(const string& s, unsigned n, double p)
SaleDate(const string& s)
CPP-Primer-5th 0 0
3. complete parameters: 
----------------
SalesData(const string& s, unsigned n, double p)
CPP-Primer-5th 3 75
4. use istream as parameters: 
----------------
SalesData(const string& s, unsigned n, double p)
SalesData()
lu 3 4.5
SalesData(istream& is)
lu 3 13.5
5. use friend method add to add two SalesData: 
----------------
ave of lhs and rhs: 4.5 25
ave of sum: 14.75
lu 6 88.5
*/