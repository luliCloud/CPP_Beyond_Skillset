#include <iostream>
#include <string>
#include <memory>
using namespace std;
/**
 * 如果你试图拷贝或赋值 unique_ptr，编译器并不总是能给出易于理解的错误信息。
 * 编写包含这种错误的程序，观察编译器如何诊断这种错误。
*/
int main() {
    unique_ptr<string> p1(new string("hello"));
    /**
     * if  we do not comment out this code, will show error as below. cannot compile
    */
    //unique_ptr<string> p2 = p1; // should show error, as unique_ptr cannot use copy to 
    // transfer the control. we should use move.
    cout << *p1 << endl;
    p1.reset(nullptr);
    return 0;
}
/**
 * use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) 
 * [with _Tp = std::__cxx11::basic_string<char>; _Dp = 
 * std::default_delete<std::__cxx11::basic_string<char> >]’
 * 
 * function "std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp> &) 
 * [with _Tp=std::string, _Dp=std::default_delete<std::string>]" 
 * (declared at line 468 of "/usr/include/c++/11/bits/unique_ptr.h") 
 * cannot be referenced -- it is a deleted function
*/