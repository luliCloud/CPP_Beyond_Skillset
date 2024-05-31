/**
 * 编写一个程序，连接两个字符串字面常量，
 * 将结果保存在一个动态分配的char数组中。重写这个程序，连接两个标准库string对象。
*/
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
using namespace std;
int main() {
    const char* c1 = "Hello ";
    const char* c2 = "world";

    unsigned len = strlen(c1) + strlen(c2) + 1;
    char *r = new char[len]();
    /**
     * 使用 strcat_s 而不是 strcat 的主要原因是提高程序的安全性。
     * 传统的 strcat 函数不检查目标缓冲区的大小，如果源字符串太长，
     * 可能会覆盖目标缓冲区之外的内存，导致数据损坏或安全漏洞。strcat_s 
     * 通过要求明确指定缓冲区大小，并在源字符串长度超出目标缓冲区容量时返回错误，来防止这种情况发生。
    */
   // strcat_s can only use in window env
    strcat(r, c1);  // len is the buffer size of the whole r. cannot overflow
    strcat(r, c2);
    cout << r << endl;

    string s1 = "Hello ";
    string s2 = "world";
    /**
     * 使用 (s1 + s2).c_str() 是正确的做法，因为 s1 + s2 返回一个临时 std::string 对象，
     * c_str() 从这个临时对象中获取一个 C 风格字符串指针，供 strcpy 或 strcpy_s 使用。
    */
    strcpy(r, (s1 + s2).c_str());
    cout << r << endl;

    return 0;
}