/** mimic the writing process of LSMtree in rocksdp
 * 注意：MemTable就是RocksDB的write buffer（写缓冲区）
 * Log-structured Merge-tree 是RocksDB的核心数据结构，为了优化写入性能设计的一种多版本并发控制
 * MVCC 数据模型。LSM tree由多层结构组成，每层都是一个不可变的有序的kv store
 * 
 * 写入：先写入Memtable，当Memtable到达一定大小后，被写入磁盘，成为Level0 的SSTable。随着时间推移
 * 数据会通过compaction，从高层合并到底层（被push向下移动，而不是合并到下层）
 * 读取：从Memtable开始，依次检查每一层的SSTable，直到找到kv存在或不存在
 * 
 * 但是这个文件中没有mimic怎么向下压缩文件到更底层。如何改变这个level的序号。
 */
#include <iostream>
#include <map>
#include <string>
using namespace std;

class LSMTree {
private:
    map<string, string> memtable; // in memory
    map<int, map<string, string>> sstables; // SSTables on disks. level -> memtable

    // write MemTable data to level0 SStable
    void flushMemTable() {
        int level = 0;
        sstables[level] = memtable;
        memtable.clear();
    }

public:
    // write data
    void put(const string& key, const string& value) {
        memtable[key] = value;
        // suppose MemTable reach a threadshold of size
        if (memtable.size() > 100) {
            flushMemTable();
        }
    }

    //read data
    string get(const string& key) {
        // firstly check Memtable
        auto it  = memtable.find(key);
        if (it != memtable.end()) {
            return it->second;
        }
        // then check every level of sstable
        for (auto& level : sstables) {
            auto& sstable = level.second;
            if (sstable.count(key)) {
                return sstable[key];
            }
        }
        return ""; // key not exist
    }
};

int main() {
    LSMTree lsmTree;
    lsmTree.put("key1", "value1");
    lsmTree.put("key2", "value2");

    cout << "Get Key1: " << lsmTree.get("key1") << endl;
    cout << "Get Key2: " << lsmTree.get("key2") << endl;

    return 0;
}

