#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>  // to_lower, ispunct
using namespace std;

/**
 * 定义一个map，关键字是家庭的姓，值是一个vector，
 * 保存家中孩子（们）的名。编写代码，实现添加新的家庭以及向已有家庭中添加新的孩子。
*/

int main() {
    map<string, vector<string>> m;
    /**
     * 逻辑是如果没有遇到@q那么先输入last name。然后开始输入数个children name，直到遇到@q
     * 开始输入下一个family 的name。可以来回跳着输入。如果想终止所有，那么连续input两个@q
    */
    for (string ln; cout << "Last name:\n", cin >> ln && ln != "@q";) {
        for (string cn; cout << "|-Children's name:\n", cin >> cn && cn != "@q";) {
            m[ln].push_back(cn);
        }
    }
    for (const auto& [key, name_list] : m) {
        for (const auto& name : name_list) {
            cout << name << " " << key << endl;
        }
    }
    return 0;
}
/**
 * Last name:
Li
|-Children's name:
Lu
|-Children's name:
@q
Last name:
Feng
|-Children's name:
juan
|-Children's name:
jin
|-Children's name:
li
|-Children's name:
@q
Last name:
Li
|-Children's name:
An
|-Children's name:
@q
Last name:
@q
juan Feng
jin Feng
li Feng
Lu Li
An Li
*/