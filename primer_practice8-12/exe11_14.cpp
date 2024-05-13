/**
 * 编写的孩子姓达到名的map，添加一个pair的vector，保存孩子的名和生日。
*/
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Families {
public:
    // pair<string, string> child; 用这种标准命名不行，child不能作为data type直接用在底下的数据结构里
    using Child = pair<string, string>;  // <name, birthday>
    using Children = vector<Child>;  // children with same family 
    using Data = map<string, Children>;  // map for all families
private:
    Data _data;
public:
    void add(const string& last_name, const string& first_name, const string& birthday) {
        Child child = {first_name, birthday};
        _data[last_name].push_back(child);
    }

    void print() const {
        for (auto const& pair : _data) {
            cout << pair.first << ":\n";
            for (auto const& child : pair.second) {
                cout << child.first << " " << child.second << endl; 
            }
            cout << endl;
        }
    }
};

int main() {
    Families families;
    auto msg = "Please enter last name, first namd and birthday: ";
    for (string l, f, b; cout << msg, cin >> l >> f >> b && l != "@q"; families.add(l, f, b)) {}
    families.print();
    return 0;
}
/**
 * Please enter last name, first namd and birthday: lu li 1990
Please enter last name, first namd and birthday: jin li 1991
Please enter last name, first namd and birthday: an li 1992
Please enter last name, first namd and birthday: feng juan 1995
Please enter last name, first namd and birthday: feng jin 1989
Please enter last name, first namd and birthday: @q

an:
li 1992

feng:
juan 1995
jin 1989

jin:
li 1991

lu:
li 1990
*/