#ifndef _STRBLOB_
#define _STRBLOB_

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>
#include <exception>
using namespace std;

class StrBlob {
public:
    using size_type = vector<string>::size_type; // similar to general size_t
private:
    shared_ptr<vector<string>> data;  // shared pointer
public:
    StrBlob() : data(make_shared<vector<string>>()) {}  // inline, data(...) is the constructor of shared_ptr
    /** 允许starblob 接受 {1,2,3} 这种花括号形式的list传给 data（） */
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
    
    size_type size() const { return data->size(); }  // infact  vec.size() func

    bool empty() const { return data->empty(); }

    /**
     * data 本身属于Strblob，但是vector<string>不属于。所以这里没有改变data 而是改变vector是没有问题的，可以用const
    */
    void push_back(const string& str) const { data->push_back(str); } 

    void pop_back() const {
        check(0, "pop_back on empty StrBlob");
        data->pop_back();
    }

    const string& front() const {
        check(0, "front on empty StrBlob");
        cout << "const front: ";
        return data->front();
    }

    const string& back() const {
        check(0, "back on empty StrBlob");
        cout << "const back: ";
        return data->back();
    }

    string& front() {
        check(0, "front on empty StrBlob");
        cout << "front: ";
        return data->front();
    }

    string& back() {
        check(0, "back on empty StrBlob");
        cout << "back: ";
        return data->back();
    }
private:
    void check(size_type i, const string& msg) const {
        if (i >= data->size()) {
            throw out_of_range(msg);
        }
    }
};

#endif