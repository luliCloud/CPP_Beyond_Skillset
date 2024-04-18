/* 使用迭代器来进行划分分数段 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<unsigned> res(11, 0);  // 100 iteself is a score segment. 11 seg
    unsigned score;
    while (cin >> score) {
        if (score <= 100) {
            ++*(res.begin() + score / 10);  // 先取ite的obj（idx），再对其增加
        }
    }
    for (int s : res) {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}