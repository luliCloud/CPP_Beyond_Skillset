/* 在 C++ 中，forward_list 是标准库中的一个容器，它实现了一个单向链表。这种类型的容器是在 C++11 标准中引入的，主要用于提供一种空间效率较高的序列容器，其特点是在插入和删除操作上比 std::list（双向链表）更为高效，尤其是在不需要双向遍历的情况下。

主要特点
单向链表：forward_list 的元素是单向链接的，每个元素只有一个指向下一个元素的指针。这与 std::list 不同，后者是一个双向链表，每个元素都有指向前一个和后一个元素的指针。
空间效率：由于只存储一个指向下一个元素的指针，forward_list 的空间开销比 std::list 小。
性能优势：forward_list 在执行插入和删除操作时，尤其是在容器的前部，表现出更高的性能，因为不需要处理双向指针。
功能限制：由于是单向链表，forward_list 不支持快速随机访问和双向遍历。容器的遍历只能从头到尾进行。
*/
#include <iostream>
#include <forward_list>
using namespace std;

/* erase odd ele in forward list */
void deleteOddEle(forward_list<int>& fl) {
    auto it = fl.begin();
    auto prev = fl.before_begin();

    for (; it != fl.end(); ) {
        if (*it & 1) {
            // erase next of prev, return next of erased idx
            it = fl.erase_after(prev);
        } else {
            prev = it;
            it++;
        }
    }

    for (int n : fl) {
        cout << n << " ";
    }
    cout << endl;
}
/* 接受一个forward_list和两个string共三个参数。函数应在链表中查找第一个string，
并将第二个string插入到紧接着第一个string之后的位置。
若第一个string未在链表中，则将第二个string插入到链表末尾。*/
void findAndInsert(forward_list<string>& fl, const string& s1, const string& s2) {
    auto curr = fl.begin(), prev = fl.before_begin();
    while (curr != fl.end()) {
        if (*curr == s1) {
            fl.insert_after(curr, s2);
            /* vector和list中的insert(it, val),将val插入it的前面，返回val的iterator
            这里insert after，将val插入到curr后面。返回val的iterator
            如果插入多个元素比如 fl.insert_after(curr, {s1,s2,s3}),
            则返回s3的iterator（最后一个元素）。而vector和list则返回第一个插入元素的迭代器*/
            return;
        } else {
            prev = curr;
            curr++;
        }
    }
    fl.insert_after(prev, s2);
}

int main() {
    forward_list<int> fl{1,2,3,4,5,6};
    deleteOddEle(fl);

    forward_list<string> fl2{"I am", "yes", "2nd"};
    string str1 = "I am", str2 = "--", str1a = "no";
    findAndInsert(fl2, str1, str2);
    for (const auto& s : fl2) {
        cout << s << " ";
    }
    cout << endl;

    findAndInsert(fl2, str1a, str2);
    for (const auto& s : fl2) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}
/*
output
2 4 6 
*/