#ifndef EX12_19_H
#define EX12_19_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>
using namespace std;

class StrBlobPtr;  // predefine for friend class useage

class StrBlob {
public:
/**
 * typedef 和 using 关键字都用于定义类型别名，但它们的语法和某些用法有所不同。
 * using 关键字是在 C++11 中引入的，提供了一种更现代、更通用的方式来声明类型别名或模板别名，
 * 而 typedef 是更传统的 C++ 类型别名声明方式。
*/
    using size_type = vector<string>::size_type;
    friend class StrBlobPtr; // friend 的类可以访问另一个类的所有成员，
    // 包括 private、public 和 protected 成员。

    StrBlobPtr begin();  // a funciton named begin(), return a StrBlobPtr
    StrBlobPtr end();
    StrBlobPtr cbegin() const;
    StrBlobPtr cend() const;

    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(const string& s) {
        data->push_back(s);
    }
    void pop_back() {
        check(0, "pop_back on empty StrBlob");  // program will terminate abnormally
        data->pop_back();
    }

    string& front() {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    string& back() {
        check(0, "back on emptry StrBlob");
        return data->back();
    }

    const string& front() const {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    const string& back() const {
        check(0, "back on emptry StrBlob");
        return data->back();
    }

private:
    shared_ptr<vector<string>> data;

    void check(size_type i, const string& msg) const {  // remember to add const here
    // otherwise not compatible with const front and end()
        if (i >= data->size()) {
            throw out_of_range(msg);  // using except lib
            /**
             * 在 C++ 中，当程序抛出异常（使用 throw 关键字），程序不会自动退出，
             * 除非这个异常没有被捕获（即没有被 catch 块处理）。
             * 如果异常没有被任何 catch 块捕获，那么程序会终止执行，这通常导致程序的非正常退出。
            */
        }
    }
};

class StrBlobPtr{
public:
    StrBlobPtr() : curr(0) {}
    /** data is the StrBlob obj member, is vector<string> */
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    /** for const StrBlob */
    StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    /** curr is idx that StrBlobPtr located at, this is overload of != */
    bool operator!=(const StrBlobPtr& p) { return p.curr != curr; } // for iteration

    string& deref() const {
        auto p = check(curr, "dereference past end"); // should return shared_ptr
        return (*p)[curr]; // deref the vector, 取vector's下标.index = curr 
    }

    StrBlobPtr& incr() {
        check(curr, "increament past end of StrBlobPtr");
        ++curr;
        return *this; // return this StrBlobPtr
    }
private:
    weak_ptr<vector<string>> wptr;
    size_t curr;  // curr 就是现在位于vector的哪个idx，因此 end（）就是size位置

    shared_ptr<vector<string>> check(size_t i, const string& msg) const {
        /**
         * std::weak_ptr<T>::lock() 方法返回一个 std::shared_ptr<T>。
         * 这个返回的 std::shared_ptr 对象会与原始的 std::shared_ptr
         * 那个最初与 std::weak_ptr 关联的）共享对象的所有权。如果原始的 std::shared_ptr 
         * 已经不存在了（即没有任何 std::shared_ptr 实例当前拥有对象），
         * 那么 lock() 返回的 std::shared_ptr 将是空的，其 bool 类型的转换结果为 false。
        */
        auto ret = wptr.lock(); // so should have at least two ptr to this memory add now
        if (!ret) {throw runtime_error("unbound StrBlobPtr");}

        if (i >= ret->size()) {throw out_of_range("msg");}
        return ret;
    }
};

/**
 * as we define constructor of StrBlobPtr inside class, we must define these
 * two function after StrBlobPtr class
*/
StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this);  // size = 0
}

StrBlobPtr StrBlob::end() {
    return StrBlobPtr(*this, data->size());
}

StrBlobPtr StrBlob::cbegin() const {
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::cend() const {
    return StrBlobPtr(*this, data->size()); // the end of vector
}
#endif