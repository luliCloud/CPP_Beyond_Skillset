#include <iostream>
#include <vector>

using namespace std;
/* capacity  在不重新分配内存空间的情况下，容器可以保存多少元素
size: container 已经保存了多少元素 */
/* 编写程序，探究在你的标准实现中，vector是如何增长的。
vector capacity: start from 0, every time when size exceed cap, curr_cap * 2*/
int main() {
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        cout << "capacity: " << v.capacity() << " " << "size: " << v.size() << endl;
        v.push_back(i);

    }

    /* reserve 是为vector预留10个位置，但如果push的元素超过10个，vector的容量还是会增加
    resize时，size会变大，但是capacity不一定会变，要看变的size是不是超过了cap*/
    v.resize(v.size() + v.size() / 2);
    cout << "capacity: " << v.capacity() << " " << "size: " << v.size() << endl;
    for (int n : v) {
        cout << n << " ";
    }
    cout << endl;

    vector<int> svec;
    svec.reserve(10);  // 使用reserve可以预先分配空间，比push_back时dynamic allocate
    // 空间的性能更高。比如 假定你希望每次读取一个字符存入一个string中，
    // 而且知道最少需要读取100个字符，应该如何提高程序的性能？
    // 用 reserve（100）就好很多
    for (int i = 0; i < 15; i++) {
        svec.push_back(i);
        cout << "capacity: " << svec.capacity() << " " << "size: " << svec.size() << endl;
    }
    return 0;
}
/*
capacity: 0 size: 0
capacity: 1 size: 1
capacity: 2 size: 2
capacity: 4 size: 3
capacity: 4 size: 4
capacity: 8 size: 5
capacity: 8 size: 6
capacity: 8 size: 7
capacity: 8 size: 8
capacity: 16 size: 9
capacity: 16 size: 10
capacity: 16 size: 11
capacity: 16 size: 12
capacity: 16 size: 13
capacity: 16 size: 14
capacity: 16 size: 15
capacity: 16 size: 16
capacity: 32 size: 17
capacity: 32 size: 18
capacity: 32 size: 19

capacity: 32 size: 30
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 0 0 0 0 0 0 0 0 0 
capacity: 10 size: 1
capacity: 10 size: 2
capacity: 10 size: 3
capacity: 10 size: 4
capacity: 10 size: 5
capacity: 10 size: 6
capacity: 10 size: 7
capacity: 10 size: 8
capacity: 10 size: 9
capacity: 10 size: 10
capacity: 20 size: 11
capacity: 20 size: 12
capacity: 20 size: 13
capacity: 20 size: 14
capacity: 20 size: 15*/