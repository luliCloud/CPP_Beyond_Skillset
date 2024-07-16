/**
 * SSTable 是LSM tree中的有序kv store。RocksDB采用不同的SSTable格式（跳表sort？）
 * 其中Block-based SSTable是默认格式
 * 
 * Block-based SSTable：数据被分割成很多数据块data block，每个block默认大小为4kb，每个快内部的
 * kv pair是sort的，并且块之间也是有序的。
 * index：rocksdb为每个sstable维护一个索引， 用于快速定位到包含目标key的block
 */
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class SSTable {
private:
    vector<vector<pair<string, string>>> ssTable; // containg many blocks. or Memtable is better
    vector<pair<string, string>> dataBlocks; // data block
    map<string, int> index; // index
public:
    // appedn kv pair to the sstable
    void add(const string& key, const string& value) {
        // suppose data block is 4KB, here simplify as fixed size
        static int blockSize = 1024 * 4;
        // 将 blockNum 声明为 static 变量意味着它在所有函数调用之间共享，
        // 并且在第一次初始化后将保留其值直到程序结束或明确地重置它。
        static int blockNum = 0;
        dataBlocks.push_back({key, value});
        index[key] = blockNum; // update index
        if (dataBlocks.size() >= blockSize) {
            blockNum++;
            ssTable.push_back(dataBlocks);
            dataBlocks.clear();
        }
    }

    // 根据kv获取值
    string get(const string& key) {
        if (index.count(key)) {
            /** this is the real one we should do if we have the sstable */
            // int block = index[key];
            // auto& db = ssTable[block];
            // for (const auto& [k,v] : db) {
            //     if (k == key) {
            //         return v;
            //     }
            // }
            
            // simplified version
            if (index.count(key)) {
                for (const auto& [k,v] : dataBlocks) {
                    if (k == key) {
                        return v;
                    }
                }
            }
        }
        return "";
        // according the index to locate the corresponding dataBlocks and find key pair
                // here simplify the searching process
    }
    
};

int main() {
    SSTable sstable;
    sstable.add("key1", "value1");
    sstable.add("key2", "value2");

    cout << "Get key1: " << sstable.get("key1") << endl;
    cout << "Get key2: " << sstable.get("key2") << endl;
    return 0;
}