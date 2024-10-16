#include <algorithm>
#include <iostream>
#include <sstream> // for stream treating
#include <list>
using namespace std;

struct Company {
    string name;
    double value;

    Company (string n, double val) : name(n), value(val) {}
};

void read_from_stream(list<Company>& l, istream& is) {
    string n;
    double val;
    is >> n >> val;

    Company c(n, val);
    l.push_back(c);
}

void print_company(const Company& co) {
    cout << co.name << " " << co.value << endl;
}

int main() {
    list<Company> l;
    for (int i = 0; i < 3; i++) {
         cout << "please input a name and a double, seperated by space: ";
        read_from_stream(l, cin);
        cin.clear();
    }

    /** 因为 std::list 不支持 std::sort()。这是因为 std::list 是一个双向链表，
     * 而 std::sort() 需要随机访问迭代器（如 std::vector 或 std::deque 的迭代器）。
     * 双向链表的迭代器不支持随机访问，这意味着你不能对 std::list 使用 std::sort() 函数。

std::sort() 的内部实现依赖于可以通过 - 运算符快速计算迭代器之间的距离，
这是链表迭代器不具备的能力。因此，你应该使用 std::list 自带的 sort() 方法，
它是专为双向链表设计的，并且接受一个比较函数。 */

    // sort(l.begin(), l.end(), [](const Company& a, const Company& b) {   
    //     return a.value > b.value; // sort from large to smaller
    // });

    l.sort([](const Company& a, const Company& b) {   
         return a.value > b.value; // sort from large to smaller
    });
    for (const auto& c : l) {
        print_company(c);
    }

    return 0;
}