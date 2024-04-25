/* 一个类中包含了另一个类作为成员变量，且另一个类没有默认构造函数。
则另一个类自己不能作为vector的成员进行初始化，但是这个类可以用来初始化vector
如果它在自己的默认构造函数中初始化了它包括的另一个类*/
#include <iostream>
#include <vector>
using namespace std;

class Default{
public:
    Default(int i) : num(i){};
    int get() { return num; }
private:
    int num;
};

class C {
public:
    Default de;
    C() : de(8) {}
};

int main() {
    // vector<Default(10)> vec(10);  // not working
    // vector<Default> vec(10); // not working
    vector<C> vec(10);
    cout << vec[0].de.get() << endl;
    return 0;
}