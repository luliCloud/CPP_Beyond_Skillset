/*编写一个函数，它的参数是initializer_list类型的对象，
函数的功能是计算列表中所有元素的和。 

在 C++ 中，std::initializer_list 是一个模板类，用于表示一个固定大小的数组。它是 C++11 标准引入的一个特性，
使得可以方便地传递一个列表的值给函数，或用于初始化对象。

构造器和函数的参数：
std::initializer_list 常用于构造函数和其他函数的参数，允许通过花括号初始化语法传递一组值。例如，你可以用它来初始化容器、创建数组，或在函数调用中传递一组预定义的值。

基于范围的循环：
std::initializer_list 对象支持迭代，可以在基于范围的 for 循环中使用，类似于数组或容器。

类型安全：
与使用 std::vector 或数组相比，std::initializer_list 更加轻量和简单。它通常在编译时解析，而不需要动态内存分配。
*/
#include <iostream>
#include <initializer_list>
#include <vector>
using namespace std;
/* this is from C++11 and above, we need to compile using C++11 and above
g++ -std=c++2b exercise6_27.cpp
c++2b stand for c++23 */
int sum(const initializer_list<int>& li) {
    int sum = 0;
    for (auto n : li) {
        sum += n;
    }
    return sum;
}

int main(int argc, char** argv) {
    vector<int> v = {1,2,3,4,55};  // using initializer list to initalize vector

    initializer_list<int> li = {1,2,3,4,4};
    cout << sum(li) << endl;
    return 0;
}
