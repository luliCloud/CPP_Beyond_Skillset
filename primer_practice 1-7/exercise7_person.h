#ifndef _EXERCISE7_PERSON_
#define _EXERCISE7_PERSON_

// we can add include and using here
#include <string> 
#include <iostream>
using namespace std;

class Person{
    friend istream& read(istream& is, Person& person);  // not belong to this class
    friend ostream& print(ostream& os, const Person& person);
private:
    string name;
    string address;
public:
    // construct
    Person() = default;
    Person(const string& sname, const string& saddress) 
    : name(sname), address(saddress) {}
    explicit Person(istream& is) { read(is, *this); } // this is pointer, need * to deref

    /*在你的Person类中提供一些操作使其能够返回姓名和地址。这些函数应该是const
    these two functions are inline function, and declare with body in h file*/
    const string& getName () const { return name; }
    const string& getAddress () const { return address; }
    
    
};

/* 读取和打印Person对象的操作 */
istream& read(istream& is, Person& person) {  // person be changed, using &
        // return is status, like success and failure
    is >> person.name >> person.address;  // redirect, put info in person
    return is;
}

ostream& print(ostream& os, const Person& person) {
    cout << "Person:print() : "; 
    os << person.name << " " << person.address;
    return os;
}

    /* how to call read func in .cpp
    if (read(std::cin, person)) {
        std::cout << "Read successful!" << std::endl;
    } else {
        std::cerr << "Failed to read person data!" << std::endl;
} 
    std::istream 和 std::ostream 类中的 operator bool() 是一个显式的类型转换函数，它检查流是否处于良好状态（没有错误）。如果流没有错误（failbit 和 badbit 都没有设置），则该函数返回 true；
    如果有错误（无论是因为 failbit 还是 badbit），则返回 false。*/

#endif
/* 
防止隐式类型转换：

在没有 explicit 关键字的情况下，如果一个构造函数只需要一个参数，编译器可以自动使用这个构造函数来将一个给定类型的值转换为构造函数所在类的类型。这种自动转换有时可能导致非预期的行为。
使用 explicit 关键字可以阻止这种隐式转换，确保类型转换时必须明确表达意图。

例子
没有 explicit 关键字

class MyClass {
public:
    MyClass(int size) { // 这个构造函数可以隐式转换 int 为 MyClass 类型
        // 初始化代码
    }
};

void function(MyClass obj) {
    // 函数体
}

int main() {
    function(10);  // 隐式转换 int 为 MyClass 类型，调用 MyClass(int)
}
在这个例子中，function(10) 调用成功执行，因为 10 被隐式转换为 MyClass 类型。

使用 explicit 关键字

class MyClass {
public:
    explicit MyClass(int size) {
        // 初始化代码
    }
};

void function(MyClass obj) {
    // 函数体
}

int main() {
    function(10);  // 错误: 不能从 'int' 隐式转换为 'MyClass'
    function(MyClass(10));  // 正确: 明确的类型转换
}
在加上 explicit 之后，function(10) 这行代码会引发编译错误，因为不再允许将 int 隐式转换为 MyClass。
这样，使用者必须显式地调用构造函数，如 function(MyClass(10))，这使得代码的意图更加清晰，减少了意外错误。

*/