/* 编写一个main函数，令其接受两个实参。把实参的内容连接成一个string对象并输出出来 */
#include <iostream>
#include <string>
using namespace std;

/* argv is an arr, containing two string (each char* is a string, i.e. char*)
command line: ./a.out hello world
output 
hello world
*/
int main(int argc, char* argv[]) {
    string str = "";
    for (int i = 1; i < argc; i++) {  // i == 0 is program name
        str += string(argv[i]) + ' ';  // convert char* to string
    }
    cout << str << endl;
    return 0;
}
/* 
./myprogram hello world
那么：

argc 将会是 3（因为有三个字符串：程序名 "myprogram"，"hello" 和 "world"）。
argv[0] 将会是 "myprogram"。
argv[1] 将会是 "hello"。
argv[2] 将会是 "world"。
*/