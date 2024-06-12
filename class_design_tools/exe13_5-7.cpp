/**
 * Copy Assignment Operator: 拷贝赋值运算符 是什么？什么时候使用它？合成拷贝赋值运算符完成什么工作？
 * 什么时候会生成合成拷贝赋值运算符？
 * copy assignment operator一个名为 operator= 的函数。当赋值运算发生时就会用到它。合成拷贝赋值运算符可以用来禁止
 * 该类型对象的赋值。如果一个类未定义自己的拷贝赋值运算符，编译器会为它生成一个合成拷贝赋值运算符。
 * 
 * Shallow copy: 将一个对象中的链接复制给另一个对象，而不是值的复制。因此速度较快，但是修改其中一个对象会影响另一个对象的值
 * Deep copy：创建一个新对象，递归的复制原对象中所有的结构数据，包括嵌套结构。新对象中所有的引用都是新对象的独立副本，
 * 不会指向原对象。
 */

/**
 * 为13.1.1节练习13.5中的 HasPtr 类编写赋值运算符。类似拷贝构造函数，你的赋值运算符应该将对象拷贝到ps指向的位置。 
 */
#include <iostream>
#include <string>
using namespace std;
class HasPtr {
private:
    string* str;
    int i;
public:
    // Constructor, not copy constructor
    HasPtr(const string& s = string()) : str(new string(s)), i(0) {}
    // Copy constructor, the first is ref to HasPtr obj
    HasPtr(const HasPtr& hp) : str(new string(*hp.str)), i(hp.i) {}

    // copy assginment operator
    HasPtr& operator=(const HasPtr& rhs) {
        string* new_str = new string(*rhs.str);
        delete str; // release mem str point to, but not destroy str ptr
        str = new_str;
        i = rhs.i;
        return *this; // assign value to every field of this obj
    }
    // destructor
    ~HasPtr() {
        delete str;
    }

    const string& getStr() {return *str;}
};

int main() {
    HasPtr has1("Hello, it's me");
    HasPtr has2 = has1;
    cout << has1.getStr() <<  " " << has2.getStr() << endl;
    return 0;
}