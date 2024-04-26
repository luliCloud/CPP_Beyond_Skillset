#include "exe7_28SalesData.h"
#include <fstream>

/*从一个文件中读取交易记录。将文件名作为一个参数传递给main。*/
int main(int argc, char **argv) {
    ifstream input(argv[1]);
    // 加入这个函数就是让输出进入一个文件，而不是输出在屏幕上
    // ofstream output(argv[2]);

    // 加入这个函数让输出进入一个文件，并且使用append模式，而不是覆盖模式
    ofstream output(argv[2], ofstream::app);

    // 因为是一个文件，应该会有很多行记录
    SalesData total; // call default constructor without arg
    if (read(input, total)) { // read the first data in total
        SalesData trans;  // call default constructor without arg
        while (read(input, trans)) {  // we modify read to catch error
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                // print(cout, total) << endl;  这个输出到屏幕
                print(output, total) << endl;
                total = trans;  // 换到下一个记录
            }
            // print(cout, total) << endl; 这个输出到屏幕
            print(output, total) << endl; // 输出到文件
        }
    } else {
        cerr << "No data?!" << endl;
    }

    return 0;
}
/*
如果读不符合条件的文件。进入不了循环 （没有加read 处理错误情况的时候）
(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ ./a.out "exe8_1.txt"
SalesData(const string& s, unsigned n, double p)
SalesData()
No data?!
注意这里call了两个constructor，因为call了没有参数的constructor后，在这个constructor里又call了main constructor

read（）没有加入处理istream错误前
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

read（）加入处理istream错误后。txt有一个mismatch信息
(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ g++ -std=c++2b exe8_6.cpp exe7_28SalesData.cpp 
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
Juan 5 21.5
Lu 2 8
Input mismatch error or read failure. // 尽管is.fail()，但是仍然会进入while循环。
Lu 2 8  // total此时保持上一个状态 就是Lu 2 8，先打印出total
sdf 0 8  // 再打印出total = trans （即使错误，也是输出了硬性匹配的trans，但是忽略了后面match不上的）
End of file reached during reading. // 再次尝试读取，但是遇到了end of file。所以退出了循环。没有内容可读了

输出到文件
(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ ./a.out "exe8_6.txt" "exe8_6output.txt"
on screen:
SalesData(const string& s, unsigned n, double p)
SalesData()
SalesData(const string& s, unsigned n, double p)
SalesData()
Input mismatch error or read failure.
End of file reached during reading. 

如果使用append mode，那么我们就运行
(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ ./a.out "exe8_6.txt" "exe8_6output.txt"
两次，验证是append还是cover
*/