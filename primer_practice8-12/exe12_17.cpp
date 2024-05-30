#include <iostream>
#include <memory>
using namespace std;

int main() {
    int ix = 1024;
    int* pi = &ix;
    int* pi2 = new int(2048);
    typedef unique_ptr<int> IntP;
    /**
     * to determine which is valid
    */
    IntP p0(ix); // invalid: 在定义一个unique ptr时，需将其绑定在new 返回的指针上
    IntP p1(pi);  //valid: 但是可能有后续的程序错误。当p1被释放时，p1指向的对象也释放了。导致
    // pi成为一个空悬指针
    IntP p2(pi2); // valid.但是pi2可能成为空悬指针
    IntP p3(&ix); // invalid: 当p3被销毁时，试图释放一个栈空间的对象
    IntP p4(new int(2048)); // valid
    IntP p5(p2.get()); // invalid. p5 and p2 point to same obj. when p5 and p2 
    // destroyed, the same memory will be released twice. 
    // p2.get() 得到p2管理的原始指针。
    return 0;
}
