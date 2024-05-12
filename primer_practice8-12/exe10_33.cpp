#include <iostream>  // no need, standard I/O from keyboard to screen. here only file input and output
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

/**
 * 编写程序，接受三个参数：一个输入文件和两个输出文件的文件名。输入文件保存的应该是整数。使用 istream_iterator 读取输入文件。
 * 使用 ostream_iterator 将奇数写入第一个输入文件，每个值后面都跟一个空格。将偶数写入第二个输出文件，每个值都独占一行。
*/
int main(int argc, char** argv) {
    if (argc != 4) {
        return -1;
    }

    ifstream ifs(argv[1]);
    ofstream odd(argv[2]), even(argv[3]);

    istream_iterator<int> in(ifs), in_eof;  // noting is istream not ifstream. iterator lib already include iostream_iterator
    ostream_iterator<int> out_odd(odd, " "), out_even(even, "\n");

    for_each(in, in_eof, [&out_odd, &out_even](const int x){
        /**
         * &out_odd 表示捕获了两个iterator的值，如果不加引用，在foreach内部不可以对其++
         * （x。。。）里内容是判断应该取哪一个iterator，out_odd or out_even. 然后用* dereference，得到修改这个iterator指向的值的权利。
         * 将i的值赋予这个iterator指向的位置（*解引用）
         * 然后在对这个值进行++，表示将该iterator移到下一个位置。也就是如果x为odd，那么odd- iterator移动。否则even移动
        */
        *(x & 0x1 == 1 ? out_odd : out_even)++ = x;
    });
    return 0;
}
/**
 * ./a.out exe10_33.txt odd.txt even.txt
 * 1 3 5 7 11 13 15 (odd.txt)
 * 
 * even.txt
 * 2
 * 4
 * 10
 * 14
*/