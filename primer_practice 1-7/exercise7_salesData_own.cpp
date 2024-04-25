#include "exercise7_salesData_own.h"

// constructor using istream and 2nd constructor without args
SalesData::SalesData(istream& is) : SalesData() {
    read(is, *this);
    cout << "SalesData(istream& is)" << endl;
}

// read data from cin to a SalesData obj
istream& read(istream& is, SalesData& item) {
    double price = 0.0;
    is >> item.bookNum >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

// add a SalesData obj to this obj
SalesData& SalesData::combine(const SalesData& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

ostream& print(ostream& os, const SalesData& item) {
    os << item.isbn() << " " << item.units_sold << " " << (double)item.revenue;
    return os;
}

// using in main.cpp to have the copy result of two SalesData obj added
// this is a friend function, so we also test whether it can use private method in SalesData class
SalesData add(const SalesData& lhs, const SalesData& rhs) {
    SalesData sum = lhs;
    sum.combine(rhs);
    cout << "ave of lhs and rhs: " << lhs.avg_price() << " " << rhs.avg_price() << endl;
    cout << "ave of sum: " << sum.avg_price() << endl;
    return sum;
}

