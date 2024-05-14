/* using lambda */
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
/* 使用 lambda 编写你自己版本的 biggies。*/
void elimdups(vector<string>& vec) {
    sort(vec.begin(), vec.end());
    auto new_end = unique(vec.begin(), vec.end());
    vec.erase(new_end, vec.end());  // vec.erase not erase alone
}

/* 用 lambda 将大于某个size 的第一个string 找出来。从依次打印从这个string开始到最后
using find_if */
void biggies(vector<string>& vec, size_t sz) {
    elimdups(vec);

    stable_sort(vec.begin(), vec.end(), [](const string& a, const string& b){
        return a.size() < b.size();
    });

    // find the first string >= sz
    // 注意要使用find_if 而不是find，因为find要用来找条件完全相同的
    auto wc = find_if(vec.begin(), vec.end(), [sz](const string& str){
        return str.size() >= sz;
    });

    // cout all string starting from wc
    // find the first str.size() >= sz and return the iterator. noting sort size
    // before, so all words before this it must be shorter.
    for_each(wc, vec.end(), [](const string& str){
        cout << str << " ";
    });
    cout << endl;
}

/* biggies edition 2,using partition method*/
void biggies2(vector<string>& vec, size_t sz) {
    elimdups(vec);

    // using partition to find first string >= sz
    // noting here can also use stable_partition, the same format, but keep relative order
    auto pivot = partition(vec.begin(), vec.end(), [sz](const string& str){
        return str.size() >= sz;  // all size >= sz will place before
    });
    // pivot point to the next one after meeting requirement

    // print out
    for (auto it = vec.cbegin(); it != pivot; it++) {
        cout << *it << " ";
    }
    cout << endl;
}

/* 标准库定义了一个名为 count_if 的算法。类似 find_if，此函数接受一对迭代器，
表示一个输入范围，还接受一个谓词，会对输入范围中每个元素执行。count_if返回一个计数值，
表示谓词有多少次为真。使用count_if重写我们程序中统计有多少单词长度超过6的部分。注意单词重复算两次 */
int countFreq(const vector<string>& vec, size_t sz) {
    int res = count_if(vec.begin(), vec.cend(), [sz](const string& str){
        return str.size() >= sz;
    });
    return res;
}

int main() {
    int x = 10;
    /* x 是lambda可以捕获的外部值，i是传入的参数即f(5)中的5.如果lambda用于容器内，则表示容器内的
    每一个元素。lambda通常用于比较，但也可以用于打印，如果在return的地方使用cout */
    auto f = [x](int i) { return i + x; };
    cout << f(5) << endl;

    vector<string> vec{"1234", "1234", "1234", "hi~", "alan", "alan", "cp"};
    biggies(vec, 3);

    vector<string> vec2{ "the", "quick", "red", "fox", "jumps", 
	"over", "the", "slow", "red", "turtle" };
    cout << countFreq(vec2, 3) << endl;
    biggies2(vec2, 4);

    // 编写一个 lambda，捕获一个局部 int 变量，并递减变量值，直至它变为0。一旦变量变为0，
    // 再调用lambda应该不再递减变量。lambda应该返回一个bool值，指出捕获的变量是否为0。
    cout << "using lambda: ";
    int i = 10;
    /* 0 本身为false。但返回true。其他数字大于1，都认为是true。！true就是false。
    i--意味着先读值再递减 */
    //auto g = [&i]()->bool {return (i == 0 ? true : !(i--)); };
    // better way: 
    auto g = [&i]()->bool {return i-- == 0; };
    while (!g()) cout << i << " ";
    cout << endl;

    return 0;
}
/*
15
hi~ 1234 alan
turtle jumps over quick slow
*/