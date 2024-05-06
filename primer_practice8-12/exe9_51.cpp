#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
设计一个类，它有三个unsigned成员，分别表示年、月和日。为其编写构造函数，
接受一个表示日期的string参数。
你的构造函数应该能处理不同的数据格式，如January 1,1900、1/1/1990、Jan 1 1900 等。
*/
class Date {
private:
    unsigned year, month, day;
public:
    Date(const string& str) {
        if (str.find_first_of("/") != string::npos) {
            convert1(str);
        } else if (str.find_first_of(",") != string::npos) {
            convert2(str);
        } else if (str.find_first_of(" ") != string::npos) {
            convert3(str);
        } else {
            year = 1990, month = 1, day = 1;
        }
    }

    void print() {
        cout << "day: " << day << " month: " << month << " year: " << year << endl;
    }
private:
    void convert1(const string& s) {
        // 1/1/1990, first 1 is month in US
        month = atoi(s.substr(0, s.find_first_of("/")).c_str());
        day = atoi(s.substr(s.find_first_of("/") + 1, 
        s.find_last_of("/") - s.find_first_of("/") - 1).c_str());
        year = atoi(s.substr(s.find_last_of("/") + 1, 4).c_str());
    }

    void convert2(const string& s) {
        // January 1,1900
        convert_month(s);
        day = atoi(s.substr(s.find_first_of("0123456789"), 
        s.find_first_of(",") - s.find_first_of("0123456789")).c_str());
        year = atoi(s.substr(s.find_first_of(",") + 1, 4).c_str());

    }

    void convert3(const string& s) {
        // Jan 1 1990
        convert_month(s);
        day = atoi(s.substr(s.find_first_of(" ") + 1, 
        s.find_last_of(" ") - s.find_first_of(" ") - 1).c_str());
        year = atoi(s.substr(s.find_last_of(" ") + 1, 4).c_str());
    }

    // helper function of convert2. assign value to class member month
    void convert_month(const string& s) {
        string m = s.substr(0, 3);
        if (m == "Jan") {
            month = 1;
        } else if (m == "Feb") {
            month = 2;
        } else if (m == "Mar") {
            month = 3;
        } else if (m == "Apr") {
            month = 4;
        } else if (m == "May") {
            month = 5;
        } else if (m == "Jun") {
            month = 6;
        } else if (m == "Jul") {
            month = 7;
        } else if (m == "Aug") {
            month = 8;
        } else if (m == "Sep") {
            month = 9;
        } else if (m == "Oct") {
            month = 10;
        } else if (m == "Nov") {
            month = 11;
        } else if (m == "Dec") {
            month = 12;
        }
    }
};

int main() {
    Date date1("12/1/1990");
    date1.print();

    Date date2("Jan 1, 2990");
    date2.print();

    Date date3("Jan 28 1787");
    date3.print();

    return 0;
    
}
/*
day: 1 month: 12 year: 1990
day: 1 month: 1 year: 299
day: 28 month: 1 year: 1787*/