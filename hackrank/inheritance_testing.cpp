#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/** 1。 可以继承多个classes
 * 在class里继承后，如果base class的constructor咩有参数，可以不在constructor里initialize。在其他函数里是可以直接调用public和protected的函数的。不需要实例化
 */
class A
{
    public:
        A(){
            callA = 0;
        }
    private:
        int callA;
        void inc(){
            callA++;
        }

    protected:
        void func(int & a)
        {
            a = a * 2;
            inc();
        }
    public:
        int getA(){
            return callA;
        }
};

class B
{
    public:
        B(){
            callB = 0;
        }
    private:
        int callB;
        void inc(){
            callB++;
        }
    protected:
        void func(int & a)
        {
            a = a * 3;
            inc();
        }
    public:
        int getB(){
            return callB;
        }
};

class C
{
    public:
        C(){
            callC = 0;
        }
    private:
        int callC;
        void inc(){
            callC++;
        }
    protected:
        void func(int & a)
        {
            a = a * 5;
            inc();
        }
    public:
        int getC(){
            return callC;
        }
};

class D : public A, B, C
{

    int val;
    public:
        //Initially val is 1
         D()
         {
             val = 1;
         }


         //Implement this function
         void update_val(int new_val)
         {
            while (new_val % 2 == 0) {
                A::func(val);  // val keep times 2
                new_val /= 2;
            }
            while (new_val % 3 == 0) { // if new_val == 1, remainder is not 0
                B::func(val);
                new_val /= 3;
            }
            while (new_val % 5 == 0) {
                C::func(val);
                new_val /= 5;
            }
            
         }
         //For Checking Purpose
         void check(int new_val) {
             update_val(new_val);
             cout << "Value = " << val << endl << "A's func called " << getA() << " times " << endl << "B's func called " << getB() << " times" << endl << "C's func called " << getC() << " times" << endl;
         } //Do not delete this line.
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int new_val;
    cin >> new_val;
    D d;
    d.check(new_val);
    return 0;
}