/* 使用迭代器来进行划分分数段 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*将两个指针相减可以表示两个指针(在同一数组中)相距的距离，
将指针加上一个整数也可以表示移动这个指针到某一位置。
但是两个指针相加并没有逻辑上的意义，因此两个指针不能相加。
*/
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