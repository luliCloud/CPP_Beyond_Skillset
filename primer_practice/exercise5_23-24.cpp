/*编写一段程序，从标准输入读取两个整数，输出第一个数除以第二个数的结果。
第二个是0，抛出异常*/
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    int i, j;
    cin >> i >> j;
    if (j == 0) {
        throw runtime_error("divisor is 0");
    }
    cout << i / j << endl;

    return 0;
}
/*
output:
1 0
libc++abi: terminating due to uncaught exception of type std::runtime_error: divisor is 0
Abort trap: 6*/