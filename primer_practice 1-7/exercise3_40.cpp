/*编写一段程序，定义两个字符数组并用字符串字面值初始化它们；
接着再定义一个字符数组存放前面两个数组连接后的结果。
使用strcpy和strcat把前两个数组的内容拷贝到第三个数组当中。*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char* s1 = "Hello";
const char* s2 = "world";

int main() {
    char s3[100];
    strcpy(s3, s1);
    strcat(s3, " ");
    strcat(s3, s2);  // s2 addto to s3, not cover

    cout << s1 <<  " " << s2 << " " << s3 << endl;
    return 0;
}