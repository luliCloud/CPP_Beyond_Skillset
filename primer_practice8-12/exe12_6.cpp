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

/** 
 * 关于创建共享共建的第二个智能指针。它需要的是第一个智能指针，而不是第一个ptr指向的原空间
*/
void sharedPtr2(shared_ptr<int> p1) {
    cout << "before copy: " << p1.use_count() << endl;
    shared_ptr<int> p2 = p1;  
    // shared_ptr<int> p2 = shared_ptr<int>(p1.get()), wrong. p1.get() obtain original 
    // address of ptr, not the p1 itself. such way make p2 thought it is the only ptr
    // pointing to this address. when p2 delete its space, the p1 become dangling ptr
    cout <<"p2: " << p2.use_count() << endl;
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

    shared_ptr<int> p1 = make_shared<int>(42);
    cout << "before first sharedPtr2 copy: " << p1.use_count() << endl;  // 1
    sharedPtr2(p1);  // 2  3. 所以这里传递的依然是p1的一个拷贝，不是p1本身。
    // 和shared_ptr<int>(p1)效果相同
    /**
     * 如果想要传递p1本身而不是copy给函数，函数定义应该是
     * void sharedPtr2(shared_ptr<int>& p1) {}
     * 但是要注意，这样的话我们就不能传递临时的shared ptr。sharedPtr2(shared_ptr<int>(p1)) is error
    */
    cout << "after first sharedPtr2 copy: " << p1.use_count() << endl;  // 1
   
    sharedPtr2(shared_ptr<int>(p1));  // create a temp p,
    cout << "after second sharedPtr2 copy: " << p1.use_count() << endl; // 1
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

for shared_ptr
before first sharedPtr2 copy: 1
before copy: 2
p2: 3
after first sharedPtr2 copy: 1
before copy: 2
p2: 3
after second sharedPtr2 copy: 1
*/