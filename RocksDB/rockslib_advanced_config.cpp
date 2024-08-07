/** RocksDB提供了许多高级配置选项，允许用户根据具体的工作负载进行细致的性能调优 
 * 
 *  怎么样运行这个文件
 *  sudo apt-get update
sudo apt-get install -y build-essential libsnappy-dev zlib1g-dev libbz2-dev libgflags-dev liblz4-dev libzstd-dev
下载编译rocksdb
git clone https://github.com/facebook/rocksdb.git  // 如果没有安装
cd rocksdb
make USE_Snappy=1 USE_ZLIB=1 USE_BZ2=1 USE_LZ4=1 USE_ZSTD=1 -j$(nproc)

回到cpp文件所在文件夹，编译程序
g++ -std=c++17 -I./rocksdb/include -L./rocksdb rockslib_advanced_config.cpp -lrocksdb -lsnappy -lz -lbz2 -llz4 -lzstd -pthread 
使用LD_LIBRARY_PATH 环境变量运行程序
export LD_LIBRARY_PATH=$(pwd)/rocksdb:$LD_LIBRARY_PATH
./a.out

*/

#include <rocksdb/db.h>
#include <rocksdb/convenience.h>
#include <iostream>
using namespace std;

void advancedConfiguration(rocksdb::DB** db, const string& dbPath) {
    rocksdb::Options options;
    options.create_if_missing = true;
    options.max_open_files = 100;
    options.write_buffer_size = 4 * 1024 * 1024; // 写缓冲区大小
    // options.block_cache_size = 1 * 1024 * 1024; // 缓冲区大小。没找到

    // 进行高级性能优化
    // 例如，调整compaction 策略
    // rocksdb::CompactionOptionsCompactionFilter compactFilter;
    // compactFilter.kCompactionStopStyle = 
    // rocksdb::CompactionStopStyle::kCompactionStopStyleTotalSize;

    /** 在 RocksDB 中，CompactionStopStyle 是用于配置压缩停止条件的枚举类型，
     * 通常与 CompactionOptionsUniversal 配合使用，而不是直接用于 
     * CompactionOptionsCompactionFilter。
     * CompactionOptionsCompactionFilter 主要用于配置压缩过滤器相关的选项。 */
    // 设置压缩样式
    options.compaction_style = rocksdb::kCompactionStyleUniversal;
    // 配置universal compaction 选项
    rocksdb::CompactionOptionsUniversal universal_compaction_options;
    universal_compaction_options.stop_style 
    = rocksdb::CompactionStopStyle::kCompactionStopStyleTotalSize;
    options.compaction_options_universal = universal_compaction_options;
    
    // open database 
    rocksdb::Status status = rocksdb::DB::Open(options, dbPath, db);
    if (!status.ok()) {
        cerr << "Fail to open database: " << status.ToString() << endl;
    }

    (*db)->SetOptions({{"level0_file_num_compaction_trigger", "4"}});
}

int main() {
    rocksdb::DB* db;
    const string dbPath = "/tmp/rocksdb_example";
    advancedConfiguration(&db, dbPath);
    // use database get put
    if (db) {
        // 使用数据库
        rocksdb::Status status;

        // 写入数据
        status = db->Put(rocksdb::WriteOptions(), "key1", "value1");
        if (!status.ok()) {
            std::cerr << "Cannot put value in database: " << status.ToString() << std::endl;
        }

        // 读取数据
        std::string value;
        status = db->Get(rocksdb::ReadOptions(), "key1", &value);
        if (!status.ok()) {
            std::cerr << "Cannot get value of key1: " << status.ToString() << std::endl;
        } else {
            std::cout << "key1: " << value << std::endl;
        }

        // 关闭数据库
        delete db;
    }

    return 0;
}
