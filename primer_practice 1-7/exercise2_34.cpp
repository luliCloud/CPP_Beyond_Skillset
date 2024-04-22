#include <iostream>
using namespace std;

/* 底层low-level const，指向常量；顶层top-level const， 本身是常量*/
int main() {
    int i = 0, &r = i; // r is reference of i
    auto a = r; // a is an int, not the reference

    const int ci = i, &cr = ci; // int can be converted to const int
    auto b  = ci; // b is an int (ci 的顶层特性被忽略)
    auto c = cr; // c is an int
    auto d = &i; // d is a pointer to int, 
    auto e = &ci; // e is a pointer to const int (对常量对象取地址是底层const)

    const auto f = ci;  // ci const is ignored, however f is still const int
    auto &g = ci;  // g is a const int reference, binding to ci

    cout << "a: " << a << endl;  // 0
    cout << "b: " << b << endl;  // 0
    cout << "c: " << c << endl;  // 0
    cout << "d: " << d << endl;  // address of i
    cout << "e: " << e << endl;  // addree of ci, diff from add of i
    cout << "f: " << f << endl;  // 0
    cout << "g: " << g << endl;  // 0
    cout << "-----------" << endl;

    a = 42; 
    b = 42; 
    c = 42;
    cout << "a: " << a << endl;  // 42 -> i is 42, ci is 0
    cout << "b: " << b << endl;  // 42
    cout << "c: " << c << endl;  // 42
    cout << "d: " << d << endl;  // address of i
    cout << "e: " << e << endl;  // addree of ci, diff from add of i
    cout << "f: " << f << endl;  // 0
    cout << "g: " << g << endl;  // 0
    return 0;
}
/* output
a: 0
b: 0
c: 0
d: 0x7ff7b9a21338
e: 0x7ff7b9a21328
f: 0
g: 0
-----------
a: 42
b: 42
c: 42
d: 0x7ff7b9a21338
e: 0x7ff7b9a21328
f: 0
g: 0
*/