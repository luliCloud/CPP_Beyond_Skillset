/** 点查是查找单个键的过程，范围查询是查找一定范围内的键. 注意这个例子中我没有design真正的MemTable
 * 和SSTable 类，所以该代码是pseudo code
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DBReader {
private:
    MemTable memTable;
    SSTable ssTable;
public:
    string pointLoopUp(const string& key) {
        // first search in MemTable
        string value = memTable.getKey(key);
        if (!value.empty()) {
            return value;
        }
        // then search in SSTable
        return ssTable.getKey(key);
    }

    vector<pair<string, string>> rangeLoopUp(const string& startKey, const string& endKey) {
        vector<pair<string, string>> results;
        // search in MemTable
        for (const auto& p : memTable) {
            if (p.first >= startKey && p.first <= endKey) {
                results.push_back(p);
            }
        }
        // Search in SSTable
        for (const auto& p : ssTable) {
            if (p.first >= startKey && p.first <= endKey) {
                results.push_back(p);
            }
        }
        return results;
    }
};

int main() {
    DBReader reader;
    // append kv to database

    cout << "Point Lookup: " << reader.pointLoopUp("key1") << endl;

    auto rangeResults = reader.rangeLoopUp("key1", "key3");
    cout << "Range loopup: " << endl;
    for (const auto& p : rangeResults) {
        cout << p.first << ": " << p.second << endl; 
    }
    return 0;
}
