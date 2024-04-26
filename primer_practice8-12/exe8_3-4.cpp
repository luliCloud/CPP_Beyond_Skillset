#include <iostream>
#include <string>
#include <fstream> // for openning file
using namespace std;

/*编写函数，以读模式打开一个文件，将其内容读入到一个string的vector中，
将每一行作为一个独立的元素存于vector中。*/
void readLine(const string& fileName, vector<string>& v) {
    ifstream ifs(fileName);
    if (ifs) {
        string line;
        while (getline(ifs, line)) {
            v.push_back(line);
        }
    }
}

/*编写函数，以读模式打开一个文件，将其内容读入到一个string的vector中，
将每一个单词作为一个独立的元素存于vector中。*/
void readWord(const string& fileName, vector<string>& v) {
    ifstream ifs(fileName);
    if (ifs) {
        string word;
        while (ifs >> word) {
            v.push_back(word);
        }
    }
}

int main() {
    vector<string> v1, v2;
    readLine("exe8_1.txt", v1);
    readWord("exe8_1.txt", v2);
    for (const auto& w : v1) {
        cout << w << endl;
    }
    for (const auto& w : v2) {
        cout << w << endl;
    }
    return 0;
}