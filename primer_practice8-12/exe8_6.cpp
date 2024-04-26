#include "exe7_28SalesData.h"
#include <fstream>

/*从一个文件中读取交易记录。将文件名作为一个参数传递给main。*/
int main(int argc, char **argv) {
    ifstream input(argv[1]);
    // 因为是一个文件，应该会有很多行记录
    SalesData total; // call default constructor without arg
    if (read(input, total)) { // read the first data in total
        SalesData trans;  // call default constructor without arg
        while (read(input, trans)) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                print(cout, total) << endl;
                total = trans;  // 换到下一个记录
            }
            print(cout, total) << endl;
        }
    } else {
        cerr << "No data?!" << endl;
    }

    return 0;
}
/*
如果读不符合条件的文件。进入不了循环
(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ ./a.out "exe8_1.txt"
SalesData(const string& s, unsigned n, double p)
SalesData()
No data?!
注意这里call了两个constructor，因为call了没有参数的constructor后，在这个constructor里又call了main constructor

(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ ./a.out "exe8_6.txt"
SalesData(const string& s, unsigned n, double p)
SalesData()
SalesData(const string& s, unsigned n, double p)
SalesData()
Lu 2 7.8
Jinfeng 3 12.6
Jinfeng 3 12.6
An 1 8
An 3 22
An 3 22
Juan 5 21.5
Lu 2 8  // if lu appear again, not adding to prev Lu
*/