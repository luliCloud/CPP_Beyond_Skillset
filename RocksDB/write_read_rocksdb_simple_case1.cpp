/** if you want to run this or other rocksdb related cpp file, you must run the 
 * install_rocksdb.ssh first to install the rockdb repo.
 */
#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <rocksdb/slice.h>
#include <iostream>
/** main API of rocksdb: open, write, read
 * bash compile the file: noting usinbg C++17 and beyond, otherwise cannot recognize
 * g++ -std=c++17 -I./rocksdb/include -L./rocksdb -o my_program write_read_rocksdb_simple_case1.cpp -lrocksdb -lz -lbz2 -lsnappy -llz4 -lzstd -pthread
 */
int main() {
    rocksdb::DB* db; // pointer to a rocksdb instance
    rocksdb::Options options; // what's this?
    options.create_if_missing = true;
    options.error_if_exists = false;

    // open database. if not exist create one.
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/rocksdb_example", &db);
    if (!status.ok()) {
        std::cerr << "Fail to open database: " << status.ToString() << std::endl;
        return 1;
    }

    // write database
    status = db->Put(rocksdb::WriteOptions(), "Key1", "Value1");
    if (!status.ok()) {
        std::cerr << "Failed to write to database: " << status.ToString() << std::endl;
        return 1;
    }

    // read data from database
    std::string value;
    status = db->Get(rocksdb::ReadOptions(), "key1", &value);
    if (!status.ok()) {
        std::cerr << "Failed to get key error: " << status.ToString() << std::endl;
    } else {
        std::cout << "Get key: " << value << std::endl;
    }

    std::string value2, key2 = "Key1";
    status = db->Get(rocksdb::ReadOptions(), key2, &value);
    if (!status.ok()) {
        std::cerr << "Failed to get key error: " << status.ToString() << std::endl;
    } else {
        std::cout << "Get " << key2 << ": " << value << std::endl;
    }

    // close dabase 
    delete db;
    return 0;
}
/**
 * 在 RocksDB 中，Options 是一个类，它包含了一些配置设置，用于控制数据库的行为。这些设置可以用于调优性能、配置功能和自定义数据库操作的各个方面。RocksDB 中有几种不同类型的 Options 类：

rocksdb::Options：用于配置数据库的一般选项。
rocksdb::DBOptions：针对数据库实例的选项。
rocksdb::ColumnFamilyOptions：针对列族（Column Family）的选项。
rocksdb::ReadOptions：针对读操作的选项。
rocksdb::WriteOptions：针对写操作的选项。
rocksdb::FlushOptions：针对刷新操作的选项。
rocksdb::CompactRangeOptions：针对压缩操作的选项。

 */