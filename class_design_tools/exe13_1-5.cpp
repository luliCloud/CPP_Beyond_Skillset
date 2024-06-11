/**
 * 如果一个构造函数的第一个参数是自身类型的引用（注意一定是引用，不一定是自身，但一定是自身的数据类型），
 * 且任何额外参数都有默认值，则此构造函数是拷贝构造函数。当使用拷贝初始化时，我们会用拷贝构造函数。
 * Sales_data::Sales_data(Sales_data rhs); // wrong, not reference
 * 
 * 假定Point是一个类类型，它有一个public的copy constructor，指出下面code哪些地方使用了copy constructor
 * Point global;
 * point foo_bar(Point arg) // 1, argument is copied
 * {
 *     Point local = arg, *heap = new Point(global); // 2: local; 3: Point *heap = new Point(global), the passed arg
 *     Point pa[4] = {local, *heap}; // 4, 5
 *     return *heap; // 6
 * }
 * 所以任何copy obj而不是指针或者引用的地方，都调用了拷贝构造函数
 */

/**
 * 给定下面的类框架，编写一个copy constructor，拷贝所有成员。你的copy constructor应该动态分配一个新string，并将
 * 对象拷贝到ps所指向的位置，而不是拷贝ps本身
 */
#include <iostream>
#include <string>
using namespace std;
class HasPtr {
public:
    HasPtr(const string& s = string()) : ps(new string(s)), i(0) {}
    /** the second copy constructor copy obj value to new allcoated mem, not copy obj itself */
    HasPtr(const HasPtr& hp) : ps(new string(*hp.ps)), i(hp.i) {}
    const string& getPs() const { return *ps; }
private:
    string *ps;
    int i;
};

int main() {
    HasPtr hs("hello, it's me");
    HasPtr has2(hs);
    cout << has2.getPs() << endl;
    return 0;
}
