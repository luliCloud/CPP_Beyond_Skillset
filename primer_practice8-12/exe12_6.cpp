#include <vector>
#include <iostream>
#include <memory>
using namespace std;

/**
 * 编写函数，返回一个动态分配的 int 的vector。将此vector 传递给另一个函数，
 * 这个函数读取标准输入，将读入的值保存在 vector 元素中。
 * 再将vector传递给另一个函数，打印读入的值。记得在恰当的时刻delete vector。
*/
/* return dynamic allocate vector */
vector<int>* allocVector() {
    return new vector<int>;
}

/* read input from cin and push into the vector */
void assignVector(vector<int>* vp) {
    int i;
    while (cin >> i) {
        vp->push_back(i);
        if (i == 4) {
            break;
        }
    }
}

/** print all ele in vector */ 
void print(vector<int>* p) {
    for (auto i : *p) {
        cout << i << " ";
    }
}

/**
 * Rewrite above task using shared_ptr
*/

/* using shared ptr to allocate a new vector space */
shared_ptr<vector<int>> allocVectorPtr() {
    /** <> is template args, tell the make_shared the type of obj
     *  () is constructor arg */
    return make_shared<vector<int>>(); 
}

/* assign vector */
void assignVectorPtr(shared_ptr<vector<int>> p) { // ptr itself is a ptr, no need add *
    int i;
    while (cin >> i) {
        p->push_back(i);
    }
}

void prinPtr(shared_ptr<vector<int>> p) {
    for (int i : *p) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vector<int>* vp = allocVector();
    assignVector(vp);
    print(vp);
    delete vp;

    cout<< "in sp: " << endl;
    shared_ptr<vector<int>> sp = allocVectorPtr();
    assignVectorPtr(sp);
    prinPtr(sp);

    return 0;
}
/**
 * 1
2
3
4
output
1 2 3 4

intput
in sp: 
1
2
3
4
1 2 3 4 
*/