#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*3 classes, Person, Professor, Student. later two inherited
Profesosor: two int memberL publications and cur_id, two functions, getdata and 
putdata. getdata get the input from the user: anme, age, and publications of the professor. putdata: print the name, age, pubs, and cur_id of the professsor..

Student: two data memberL marks (arr of size 6) and cur_id. functions: getdata and putdata. get data get the input from the user: the name, age, and the marks of the students in 6 subjects. putdata: print name, age, sum of the marks and the cur_id of the student.

For each Prof and Student, sequential id's should be assigned to them starting from 1. 

When type in 1, new prof instance. type in 2, student */

class Person {
public:  
    int cur_id, age;
    string name;
public:
    // constructor cannot be virtual
    virtual void getdata() {}
    virtual void putdata() {}
};

class Professor : public Person{ // remember is one ':'
    // already have cur_id, age, name;
private:   
    int publications;
    static int ids;
public:
    Professor() {
        ids++;
        cur_id = ids;
    }
    virtual void getdata() {
        cin >> name >> age >> publications;  
        // can only modify when name and age is public
    }
    
    virtual void putdata() {
        cout << this->name << " "
            << this->age << " "
            << this->publications << " "
            << this->cur_id << endl;
    }
};

int Professor::ids = 0;

class Student : public Person {
private:
    static int ids; // only belong to Student class
    vector<int> marks;
public:
    Student() {
        ids++;
        this->cur_id = ids;
    }
    
    virtual void getdata() {
        cin >> name >> age;
        for (int i = 0; i < 6; i++) {
            int mark;
            cin >> mark;
            marks.push_back(mark);
        }
    }
    
    virtual void putdata() {
        int sum = 0;
        for (int n : marks) {
            sum += n;
        }
        cout << this->name << " "
            << this->age << " "
            << sum << " "
            << this->cur_id << endl;
    }
};
int Student::ids = 0;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    
    while (n--) {
        int type;
        cin >> type;
        if (type == 1) { // as we already define how many should input in each class, the cin will auto stoped when reading all informaiton. for marks, we assign the slots only for 6
            Professor p1;
            p1.getdata();
            p1.putdata();
        } else {
            Student s;
            s.getdata();
            s.putdata();
        }
    }
    
    return 0;
}
