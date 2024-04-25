#ifndef _CONSTEXPR_
#define _CONSTEXPR_
#include <iostream>
#include <vector>
using namespace std;

class Example {
public:
    static double test_rate;
    static constexpr double rate = 6.5;  // constexpr可以在class初始化，但需要在cpp中再声明一次
    static const int vecSize= 20;  // static中只有常量整型的可以在class内初始化
    static vector<double> vec;  // static vector不可以在。h中初始化。
};

double Example::test_rate = 2.4;  // need to define here
#endif