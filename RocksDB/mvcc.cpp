/**
 * MVCC（Multiversion Concurrency Control，多版本并发控制）是一种用于数据库管理系统的并发控制方法。它通过维护多个版本的数据来实现并发控制，从而允许多个事务同时读取和写入数据，而不会相互冲突。以下是 MVCC 的主要特点和工作原理：

多版本存储：数据库中的每个数据项都有多个版本，每个版本对应一个特定的时间戳或事务标识。当事务更新数据时，旧版本不会被覆盖，而是创建一个新的版本。

时间戳或事务ID：每个版本的数据项都有一个时间戳或事务ID，标识其创建时间或创建它的事务。这有助于数据库在读取数据时选择合适的版本。

读写操作分离：读操作读取数据时，可以选择最适合自己的版本，而不必等待写操作完成。这样读操作不会阻塞写操作，提高了系统的并发性能。

事务隔离级别：MVCC 支持不同的事务隔离级别，如快照隔离（Snapshot Isolation）、可重复读（Repeatable Read）等，以保证数据的一致性和隔离性。

垃圾收集：由于多个版本的数据可能会占用大量存储空间，MVCC 系统通常会有一个垃圾收集机制，用于删除不再需要的旧版本数据，以节省存储空间。

总的来说，MVCC 通过维护多个数据版本来实现高效的并发控制，避免了读写锁定的问题，从而提高了数据库的性能和可扩展性。
 */
/** rocksdb support mvcc. 支持快照读取和并发写入 */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class MVCCStore {
private:
    unordered_map<string, vector<string>> versions; // key->{different value at dif time}

public:
    // insert value of new version
    void put(const string& key, const string& value, int version) {
        if (!versions.count(key)) {
            versions[key].push_back("NULL"); // place holder with empty data
        }
        versions[key].push_back(value);
    }

    // obtain specified version's value
    string get(const string& key, int version) {
        auto it = versions.find(key);
        if (it != versions.end() && version < it->second.size()) {
            return it->second[version];
        }
        return ""; // if version not exist
    }
};

int main() {
    MVCCStore db;
    db.put("key1", "value1", 1);
    db.put("key1", "value2", 2);
    cout << "Get key 1 version 1: " << db.get("key1", 1) << endl;
    cout << "Get key 2 version 2: " << db.get("key1", 2) << endl;
    return 0;
}