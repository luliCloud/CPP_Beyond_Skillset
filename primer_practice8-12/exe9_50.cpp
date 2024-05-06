#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* 注意 atoi 和 stoi 都可以用来转换string 到数字，而不是atoi只能处理char*/
int calcInt(const vector<string>& vec) {
    int sum = 0;
    for (const string& s : vec) {
        sum += atoi(s.c_str()); 
    }
    return sum;
}

float calcFlo(const vector<string>& vec) {
    float sum = 0.0;
    for (const string& s : vec) {
        sum += atof(s.c_str());
    }
    return sum;
}

int main() {
    vector<string> vec = {"10", "100", "1.6"};
    cout << calcInt(vec) << endl;
    cout << calcFlo(vec) << endl;

    vector<string> vec2 = {"10", "100", "1.5"};
    cout << calcInt(vec2) << endl;
    cout << calcFlo(vec2) << endl;
    return 0;
}
/*
111
111.6
111
111.5
*/