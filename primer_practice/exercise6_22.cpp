/* 交换两个指针（指向的地址） */
#include <iostream>
#include <string>
using namespace std;

/* p and q is reference of int pointer*/
void swap(int*& p, int*& q) {
    auto tmp = p;
    p = q;
    q = tmp;
}

int main() {
    int i = 1, j = 2;
    int* p = &i;
    int* q = &j;
    cout << p << " " << q << " " << i << " " << j << endl;

    swap(p, q);
    cout << p << " " << q << " " << i << " " << j << endl;
    return 0;
}
/* output
0x7ff7b1d27338 0x7ff7b1d27334 1 2
0x7ff7b1d27334 0x7ff7b1d27338 1 2
*/