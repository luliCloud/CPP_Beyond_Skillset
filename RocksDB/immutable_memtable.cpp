/** Memtable 是RocksDB中的内存存储引擎，每当MemTable达到一定大小后，就会被转成Immutable MemTable
 * 并处罚一个新的MemTable的创建
 */
#include <iostream>
#include <string>
using namespace std;

class MemTable {
private:
    bool isImmutable;
public:
    MemTable() : isImmutable(false) {}

    // lable Memtable as immutable
    void flush() {
        isImmutable = true;
        cout << "MemTable has been flused to disk and marked as immutable" << endl;
    }

    bool canWrite() {
        return isImmutable;
    }
};

int main() {
    MemTable mt;
    mt.flush();
    if (!mt.canWrite()) {
        MemTable newMt; // continue write to new table
    }
    return 0;
}

