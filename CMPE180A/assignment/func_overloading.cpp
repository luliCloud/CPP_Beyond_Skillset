#include <iostream>
using namespace std;

// default argument example 
void default_args(int arg1, int arg2=-3) {
    cout << arg1 << " " << arg2 << endl;
}

int avg(int a, int b) { return (a+b)/2; }
int avg(double a, double b) { return (a+b); }

template <typename T>
T avg(T a, T b) {return (a+b)/2;}

int main () {
	double a = avg<int> (5,6);  // noting return type will be the same as input, 
    // i.e. int. so return 5 then change to 5.0
	double b = avg(5.0, 6.0);
	// avg(5,6); compile error
    cout << a <<  " " << b << endl;

    default_args(1);
    default_args(1,2);
    return 0;
}