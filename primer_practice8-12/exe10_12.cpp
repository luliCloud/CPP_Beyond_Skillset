#include <iostream>
#include "exe7_28SalesData.h"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


inline bool compareIsbn(const SalesData& sd1, const SalesData& sd2) {
    return sd1.isbn().size() < sd2.isbn().size();
}

/* both sort and stable_sort can accept class rather than basic data type */
int main() {
    SalesData sd1("aa"), sd2("aaaa"), sd3("aaa"), sd4("z"), sd5("aaaaz");
    vector<SalesData> vec{sd1,sd2,sd3,sd4,sd5};
    stable_sort(vec.begin(), vec.end(), compareIsbn);
    for (const auto& sd : vec) {
        cout << sd.isbn() << " ";
    }
    cout << endl;

    vector<SalesData> vec2{sd1,sd2,sd3,sd4,sd5};
    sort(vec2.begin(), vec2.end(), compareIsbn);
    for (const auto& sd : vec2) {
        cout << sd.isbn() << " ";
    }
    cout << endl;
    return 0;
}
