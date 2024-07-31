/** WAL是一种常见的持久化机制，所有的写操作在应用到数据库之前，都先记录到日志中
 * 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

/* Define WAL */
class WAL {
private:
    /** fstream 是 C++ 标准库中的一个类，用于文件输入和输出操作。它是一个模板类，
     * 可以处理文本文件和二进制文件。fstream 结合了 
     * ifstream（用于文件输入操作）和 ofstream（用于文件输出操作）的功能，可以同时进行文件的读写操作。 */
    fstream logFile; // lofFile 对象不仅包含了打开文件的信息，还提供了多种函数和运算符用于操作文件。
public: 
    WAL(const string& filename) {
        // if file not exist, create one in curr wd
        logFile.open(filename, ios::app); // app表示以追加模式打开，不会覆盖文件中已有的数据
    }

    ~WAL() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    // record write ope to log
    void log(const string& key, const string& value) {
        logFile << key << " " << value << endl;
    }

    // recover ope, replay logs
    void recover(unordered_map<string, string>& store) {
        ifstream readFile("log.txt");
        string line, key, value;

        while (getline(readFile, line)) {
            istringstream iss(line);
            if (getline(iss, key, ' ') && getline(iss, value)) {
                store[key] = value;
            }
        }
        readFile.close();
    }
};

int main() {
    WAL wal("log.txt");
    unordered_map<string, string> store;
    
    wal.log("key1", "value1");
    wal.log("key2", "value2");

    wal.recover(store);

    for (const auto& [k, v] : store) {
        cout << k << " " << v << endl;
    }
    return 0;
}