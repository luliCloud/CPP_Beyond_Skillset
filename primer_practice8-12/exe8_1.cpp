/*编写函数，接受一个istream&参数，返回值类型也是istream&。
此函数须从给定流中读取数据，直至遇到文件结束标识时停止。它将读取的数据打印在标准输出上。
完成这些操作后，在返回流之前，对流进行复位，使其处于有效状态。*/
#include <iostream>
#include <string>
#include <fstream> // for openning file
using namespace std;

istream& read(istream& is) {
    string line;
    while (getline(is, line)) {
        cout << line << endl;
    }
    is.clear();
    return is;
}

int main() {
    // read cin
    istream& is = read(cin);  // noting must use &，因为流对象不可复制
    cout << is.rdstate() << endl;

    // read file
    ifstream file("exe8_1.txt");
    istream& is2 = read(file);  // cannot use is to overload here
    cout << is2.rdstate() << endl;

    return 0;
}
/*
(base) Lis-MacBook-Pro:primer_practice8-12 lilv$ ./a.out
i am a tree
i am a tree
0D
this is a test file
when you meet this line
indicate already the end of 
this file. 
0
*/

/*
// output 0D: 
0D 在十六进制表示是 13，在二进制中为 1101。这表明 failbit, badbit, 和 eofbit 都被设置了，只有 goodbit 是没有被设置的。
这种状态表示流同时遇到了多种错误：已达到文件末尾（eofbit），输入/输出操作失败（failbit），且流本身已损坏（badbit）。

std::istream 类（is 变量）:
is 是 std::istream 类的一个实例。这个类是 C++ 标准库中用于输入流操作的基类，可以用来从各种输入源（如键盘输入、文件等）读取数据。
rdstate() 成员函数:
rdstate() 是 std::istream 类的一个成员函数，用于返回当前流的状态。流状态是用来指示流的当前健康状况，如是否存在错误等。
返回值:
rdstate() 返回一个整数，该整数表示流的状态。返回值是 std::ios_base::iostate 类型，它是一个位字段，用于表示不同类型的错误状态：
std::ios_base::goodbit：表示没有错误，值为 0。
std::ios_base::badbit：表示流已损坏，无法继续使用。
std::ios_base::failbit：表示一个输入或输出操作失败了，但流仍然可用。
std::ios_base::eofbit：表示流已到达输入的末尾。
通常，这些状态可以组合使用。例如，如果 failbit 和 eofbit 同时被设置，表示最后的输入操作因到达文件末尾而失败。*/