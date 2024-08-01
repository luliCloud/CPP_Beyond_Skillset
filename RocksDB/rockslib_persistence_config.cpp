/** RocksDB提供了多种持久化相关的config，如WAL的禁用，SSTable的压缩策略等 */
// compression 选项用不上。还没有debug
#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/convenience.h>
#include <rocksdb/options.h>
using namespace std;

// db is the pointer to the database
void configurePersistence(rocksdb::DB** db, const string& dbPath) {
    // forbid WAL
    rocksdb::Options options;
    options.create_if_missing = true;
    // options.disableWAL = false;  // noting rocksdb does not have disableWAL options

    rocksdb::WriteOptions write_options;
    write_options.disableWAL = true; // set to true to forbid WAL

    // set compression config
    // options.compression = rocksdb::kSnappyCompression; // choose a compression algo

    // open the database
    /** 首先，rocksdb::DB* db 是一个指向数据库对象的指针。当你调用 rocksdb::DB::Open 函数时，
     * 它需要一个指向指针的指针 (DB**) 来在函数内部分配内存并将指针返回给调用者。
     * 因此，即使 db 是一个指针，你仍需要传递它的地址 (&db) 给 Open 函数。 */
    rocksdb::Status status = rocksdb::DB::Open(options, dbPath, db); // remember to add &
    if (!status.ok()) {
        cerr << "Failed to open database: " << status.ToString() << endl;
    }
}

// how to run this cpp
// g++ -std=c++17 -I./rocksdb/include -L./rocksdb rockslib_persistence_config.cpp -lrocksdb -lz -lbz2 -lsnappy -llz4 -lzstd -pthread
int main() {
    rocksdb::DB* db;
    string dbPath = "/tmp/rocksdb_example";
    
    configurePersistence(&db, dbPath);
    // using database
    rocksdb::Status status;
    status = db->Put(rocksdb::WriteOptions(), "key1", "value1");
    if (!status.ok()) {
        cerr << "Cannot put value in database: " << status.ToString() << endl;
    }

    string value;
    status = db->Get(rocksdb::ReadOptions(), "key1", &value); // noting is ReadOptions
    if (!status.ok()) {
        cerr << "Cannot get value of key1: " << status.ToString() << endl;
    } else {
        cout << "key1: " << value << endl;
    }

    delete db;
    return 0;
}