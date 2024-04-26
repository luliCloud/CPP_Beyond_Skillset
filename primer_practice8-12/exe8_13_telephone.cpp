/* 从一个文件里读人的名字和电话号码 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>  // deteremine the isdigit and isalpha
#include <string>
#include <vector>
using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const string& str) {
    return isdigit(str[0]);
}

string format(const string& str) {
    return str.substr(0, 3) + "-" + str.substr(3, 3) + "-" + str.substr(6);
}

int main() {
    ifstream ifs("exe8_13_tele.txt");
    if (!ifs) {
        cerr << "No data!" << endl;
        return -1;
    }

    string line, word;
    istringstream iss;
    vector<PersonInfo> people;
    // read line record from file and store in people vector
    while (getline(ifs, line)) {
        PersonInfo p;
        iss.clear();
        iss.str(line);
        iss >> p.name;
        while (iss >> word) {
            p.phones.push_back(word);
        }
        people.push_back(p);
    }

    // read record from people vector and print them on screen using 
    // valid (phone is digit)) and format method
    for (const auto& p : people) {
        ostringstream formatted, badNums;
        for (const auto& ph : p.phones) {
            if (!valid(ph)) {
                badNums << " " << ph;  // store the invalid phone number in badNums oss
            } else {
                formatted << " " << format(ph);  // convert phone num into xxx-xxx-xxxx 
            }
        }
        // 注意这个if else在外面。我们读完了所有的电话号码后，一次性打出来。
        if (badNums.str().empty()) {  // no invalid info input, indicating phone is valid
            // 注意我们将string放入了oss，但是调用时此string时需要使用str（）这个函数
            cout << p.name << " " << formatted.str() << endl;
        } else {
            cerr << "input error: " << p.name
            << " invalid number(s) " << badNums.str() << endl;
        }
    }

    return 0;
}

/*
input:
lu 2224447777 3338889990
an 3838293833 3838492934
jin 88283848582 huhiadf
juan 7778293849 384832839
output:
lu  222-444-7777 333-888-9990
an  383-829-3833 383-849-2934
juan  777-829-3849 384-832-839
input error: jin invalid number(s)  huhiadf
理论上应该是jin在juan前面输出错误信息，因为cerr没有缓冲，cout有缓冲。但是具体情况仍要看当时的compiler
*/