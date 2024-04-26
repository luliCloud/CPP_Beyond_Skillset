/* 使用istringstream 打印 */
#include <iostream>
#include <sstream>
#include <fstream> // for ifstream
#include <vector>
#include <string>
using namespace std;

istream& print(istream& is) { // noting here is input, not const string
    string buf;
    while (is >> buf) {
        cout << buf << endl;
    }
    return is;
}

/*将来自一个文件中的行保存在一个vector中。
然后使用一个istringstream从vector读取数据元素，每次读取一个单词 */
void readFile(const string& fileName) {
    ifstream ifs(fileName);
    if (!ifs) {
        cerr << "No data" << endl;
        return;
    }

    vector<string> vecLine;
    // istringstream iss(ifs); // iss 只能读string，不能读流
    string line;
    while (getline(ifs, line)) {
        vecLine.push_back(line);
    }

    for (const auto& s : vecLine) {
        istringstream iss(s);
        string w;
        while (iss >> w) {
            cout << w << ", ";
        }
        cout << endl;
    }
}

int main() {
    // istringstream is istream too, not the string is istream
    istringstream iss("Hello World, !");
    print(iss);

    readFile("exe8_1.txt");  // abs path is uneccesary

    return 0;
}
/*
output: 
Hello
World,
!
this, is, a, test, file, 
when, you, meet, this, line, 
indicate, already, the, end, of, 
this, file., 

*/