/* 编写函数的声明，令其接受两个int形参并返回类型也是int；然后声明一个vector对象，令其元素是指向该函数的指针。
然后对这些函数实现加减乘除 */
#include <iostream>
#include <vector>

using namespace std;
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    // noting how to declare a func and put in vector
    int func(int, int); // declare
    vector<decltype(func)*> v;
    v.push_back(add);
    v.push_back(subtract);
    v.push_back(multiply);
    v.push_back(divide);
    for (auto i : v) {
        cout << i(2, 1) << " " << i(2, 0) << endl;
    }
    return 0;
}
/*
3 2
1 2
2 0
2 0
*/