/** 监控和日志对于维护数据库的健康状态，性能调优，和问题排查至关重要 
 * 监控指标和日志
 * 监控指标包括但不限于CPU使用率，内存使用率，磁盘I/O，网络流量，查询延迟，错误率等。RocksDB不但提供了多种监控指标，
 * 还可以通过其API获取
*/
#include <rocksdb/db.h>
#include <rocksdb/statistics.h>
#include <iostream>
using namespace std;

void printDBStates(rocksdb::DB* db) {
    rocksdb::Statistics* stats = db->GetOptions().statistics.get();
    if (stats) {
        // print all collecting stats information
        string stat = stats->ToString();
        cout << "Database statistics:\n" << stat << endl;
    } else {
        cout << "No statistics collected." << endl;
    }
}

int main() {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/rocksdb_example", &db);  // a pointer to db
// noting func(&db) -> void func(DB* db): &db is passed parameter, corresponding to *db in arg of defined func
// &*db -> **db
    if (!status.ok()) {
        cerr << "Failed to open database" << status.ToString() << endl;
    } else {
        printDBStates(db);
    }

    delete db;
    return 0;
}
/**
 * g++ -std=c++17 -I./rocksdb/include -L./rocksdb rockslib_advanced_config.cpp -lrocksdb -lsnappy -lz -lbz2 -llz4 -lzstd -pthread 
 * export LD_LIBRARY_PATH=$(pwd)/rocksdb:$LD_LIBRARY_PATH
 * 
 * key1: value1  (output)
 */