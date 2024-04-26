/* define our own SalesData Class */
#ifndef _SALES_DATA_
#define _SALES_DATA_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SalesData {
    /* 这几个函数用于在main里读写data，不需要实例化SalesData */
    friend istream& read(istream& is, SalesData& item);
    friend ostream& print(ostream& os, const SalesData& item);
    // lhs: left hand side
    friend SalesData add(const SalesData& lhs, const SalesData& rhs);
public:
    /* this is a good example of delegating constructor */
    // main constructor. first one will be used for all following. p is single unit price
    SalesData(const string& s, unsigned n, double p) : bookNum(s), units_sold(n), revenue(p * n) {
        cout << "SalesData(const string& s, unsigned n, double p)" << endl;
    }

    // overload, using first constructor
    SalesData() : SalesData("", 0, 0.0) {
        cout << "SalesData()" << endl;
    }

    // overload, using first constructor with one auto arg
    SalesData(const string& s) : SalesData(s, 0, 0.0) {
        cout << "SaleDate(const string& s)" << endl; 
    }

    // using the second constructor without arg. we will define it in SalesDate.cpp
    SalesData(istream& is);

    // get bookNum
    string isbn() const { return bookNum; }

    // add one SalesData to this (modifying)
    SalesData& combine(const SalesData& rhs);

private:
    string bookNum;
    unsigned units_sold = 0;
    double revenue = 0.0;
private:
    inline double avg_price() const;
};

// calculate average price of each sold unit
inline double SalesData::avg_price() const {
    return units_sold != 0 ? revenue / units_sold : 0;
}

// all friend functions need to be declared in header file
istream& read(istream& is, SalesData& item);
ostream& print(ostream& os, const SalesData& item);
SalesData add(const SalesData& lhs, const SalesData& rhs);

#endif