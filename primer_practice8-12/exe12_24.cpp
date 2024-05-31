/**
 * 编写一个程序，从标准输入读取一个字符串，存入一个动态分配的字符数组中。
 * 描述你的程序如何处理变长输入。测试你的程序，输入一个超出你分配的数组长度的字符串。
*/
#include <iostream>
using namespace std;
int main() {
    cout << "How long do you want the string? ";
    int size{ 0 };
    cin >> size;
    /** 有（）是所有字符初始化为\0,确保字符串是正确终止的。假设没有初始化只是分配内存，最后一个
     * 字符我们默认是不写入的，这样如果最后一个字符不是\0，首先它不会是一个string，其次它有可能
     * 没办法正常终止
     * 
     * 这行代码依然会分配足够的内存空间来存储 size + 1 个 char 类型的元素，
     * 但这些字符的初始值是未定义的。它们的内容取决于内存分配时的内存状态，
     * 可能包含任何随机数据。这意味着如果你立即使用这个数组作为字符串，
     * 可能会遇到问题，因为字符串可能不会有正确的终止 null 字符，
     * 导致输出或处理字符串时出现错误（例如，打印出随机内存数据或导致程序崩溃）。*/
    char* input = new char[size + 1]();
    /**
     * 这一行调用 cin.ignore() 函数来忽略掉之前留在输入流中的任何字符，包括可能的换行符。
     * 这通常用于清空输入缓冲区，以确保下一个输入操作（如 cin.get()）接收预期的输入，
     * 而不是之前的遗留数据
    */
    cin.ignore();
    cout << "input the string: ";
    /**
     * 在 C++ 中使用 cin.get(input, size + 1) 时，
     * 其含义是要从输入流中读取最多 size + 1 - 1 个字符到 input 指向的字符数组中。
     * input是我们要输入的字符。+1 留给\0
    */
    cin.get(input, size + 1);
    cout << "INPUT string is: " << input << endl;
    delete[] input;

    return 0;
}
/**
 * How long do you want the string? 8     
input the string: hellow wwolds
INPUT string is: hellow w
*/