#include <iostream>
#include <string>
using namespace std;

/** define execption here
 * 如果你自定义了一个异常类，并且在函数中抛出了这个类的实例，
 * 系统会知道这是一个异常，并会按照标准的异常处理流程来处理它。
 */
class badLengthExecption {
private:
    int n;
public:
    badLengthExecption(int errorNumber) : n(errorNumber) {}

    int what() { return n; }
};

bool checkUserName(string userName) {
    bool inValid = false;
    int n = userName.size();

    // self-define whether the input string len is shorter
    if (n < 5) {
        throw badLengthExecption(n);  // directly construct a badLenExept without name
    } 

    // self-determine whether valid
    for (int i = 0; i < n - 1; i++) {
        if (userName[i] == 'w' && userName[i + 1] == 'w') {
            inValid = true;
            break;
        }
    }
    return inValid;
}

int main() {
    int n; 
    cin >> n;
    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        // checkUserName will throw exepction if detect abnormal case
        try {
            bool inValid = checkUserName(str);
            if (inValid) {
                cout << "Invalid" << endl;
            } else {
                cout << "Valid" << endl;
            }
        } catch (badLengthExecption e) {
            cout << "Too short: " << e.what() << endl;
        }
    }
}