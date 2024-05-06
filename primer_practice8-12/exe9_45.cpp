#include <iostream>
#include <string>
using namespace std;

/*接受一个表示名字的string参数和两个分别表示前缀（如"Mr."或"Mrs."）和后缀（如"Jr."或"III"）的字符串。
使用迭代器及insert和append函数将前缀和后缀添加到给定的名字中，将生成的新string返回。*/
string addPreAndSuffix(string& str, const string& pre, const string& su) {
    // insert prefix
    str.insert(str.begin(), pre.cbegin(), pre.cend());
    // append suffix and return the new string
    return str.append(su);
}

/* using len and insert only */
string addPreAndSuffix2(string& str, const string& pre, const string& su) {
    str.insert(0, pre);
    str.insert(str.size(), su);
    return str;
}

int main() {
    string name{"Lu"};
    cout << addPreAndSuffix(name, "Miss.", " Jr.") << endl;

    string name2{"Lu"};
    cout << addPreAndSuffix(name2, "Miss.", " Jr.") << endl;

    return 0;
}
/*
Miss.Lu Jr.
Miss.Lu Jr.*/