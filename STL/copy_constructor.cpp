#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Person{
public:   
    char* name;
public:
    Person(const char* s) {
        name = new char[strlen(s) + 1];
        strcpy(name, s);  // copy s content into name
        cout << "Person() called" << endl;
    }
    /*override: copy constructor*/
    Person( const Person& other ) {
        name = new char(strlen(other.name) + 1);
        strcpy(name, other.name);
        cout << "copy Person() called" << endl;
    }

    void print() {
        cout << "Yes" << endl;
    }

    ~Person() {
        cout << "~Person() called" << endl;
        delete[] name;
    }
};

Person f() {
    Person p1("P1");
    return p1;
}

Person copy_func(char* who) {
    Person local (who); // output: Person() caleed
    local.print(); // create a obj here, call ctor. output: Yes
    return local; // output: ~Person() called
    // 理论上这里call copy constructor，因为要return obj
    // call copy ctor, when return an obj copy from created obj
    /**
     * 但是这里进行了compiler进行了返回值优化，RVO，return value optimization。用于消除对象在返回时不必要的拷贝操作。提高程序效率
    */
}

Person nocopy_func(char* who) {
    return Person(who); // 系统优化，认为不需要拷贝构造，因为临时变量没有任何用途，所以也不用create一个再copy
    // output: Person() called   ~Person() called
}


int main() {
    char* who = "An";
    copy_func(who);
    cout << "no copy begin" << endl;
    nocopy_func(who);
    return 0;
}
/**
 * Person() called
Yes
~Person() called
no copy begin
Person() called
~Person() called
*/