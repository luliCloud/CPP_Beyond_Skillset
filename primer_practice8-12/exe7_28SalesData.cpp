#include "exe7_28SalesData.h"

// constructor using istream and 2nd constructor without args
SalesData::SalesData(istream& is) : SalesData() {
    read(is, *this);
    cout << "SalesData(istream& is)" << endl;
}

// read data from cin to a SalesData obj。我们添加了处理流的错误信息在这里
istream& read(istream& is, SalesData& item) {
    double price = 0.0;
    if (is >> item.bookNum >> item.units_sold >> price) {
        item.revenue = price * item.units_sold;
    } else {
        if (is.eof()) {
            cerr << "End of file reached during reading. " << endl;
        } else if (is.fail()) {
            cerr << "Input mismatch error or read failure." << endl;
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore remaining mismatch in this line
        } else if (is.bad()) {
            cerr << "Critical system-level error during reading." << endl;
        }
    }
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