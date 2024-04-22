/*编写一段程序，从标准输入读取两个整数，输出第一个数除以第二个数的结果。
第二个是0，用 try catch 抛出异常*/
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    int i, j;
    cout << "please enter two number: " << endl;
    while (cin >> i >> j) {
        /* 使用 try catch时，异常信息不会由main 函数处理并打印，而需要我们用err.waht()来
        捕捉并显示。*/
        try {
            if (j == 0) {
                throw runtime_error("the divisor is 0!");
            }
            cout << i / j << endl;
        }
        catch (runtime_error err) {
            // 注意 err.what()通常紧跟catch语句。不要讲char c定义在这个句子之前，会出现编译错误。另外
            // err的作用域也仅限于catch 块内
            cout << err.what() << "\nTry Again? Enter y or n: " << endl;
            char c;
            cin >> c;
            if (c != 'y') {
                break;
            }
        }
        cout << "Please input two numbers: " << endl;
    }

    return 0;
}
/*
在 C++ 中，如果你不使用 try-catch 块来捕获一个异常，而该异常在函数中被抛出（如通过 throw std::runtime_error("...");），该异常将向上传递到调用栈，直到找到相应的 catch 块来处理它。如果没有任何 catch 块捕获这个异常，它最终会到达主函数的外部，程序会终止并由运行时环境处理这个未捕获的异常。

运行时环境处理未捕获的异常
当异常未被捕获时，C++ 的标准行为是调用 std::terminate()，这通常导致程序异常终止。在很多实现中，这还会导致错误信息的打印，这就是为什么当你不使用 try-catch 时可能看到异常信息（如 std::runtime_error 所带的信息）输出到控制台或其他错误日志中。

这种错误信息的输出并不是由 throw 语句直接控制的，而是由运行时系统或操作系统的标准错误处理机制处理的。这可能包括打印出异常的描述信息，这些信息是通过调用异常对象的 what() 方法获得的。

使用 try-catch 时的行为
当你使用 try-catch 块捕获异常时，你对异常的处理方式负有责任。这包括决定是否打印错误消息、是否重新抛出异常、或是执行其他一些错误恢复或日志记录的操作。在 catch 块中，你可以使用 e.what() 来获取和输出异常描述。如果你选择不调用 e.what()，那么异常信息就不会被自动输出，因为你已经接管了异常处理的责任。
*/