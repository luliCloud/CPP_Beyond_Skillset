/**
 * RocksDB支持多种压缩算法，如Sanppy，LZ4， ZSTD等。可以减少SSTable的磁盘占用。
 * 同时RocksDB提供了Block Cache和Table Cache来缓存热点数据，提高读取性能。
 * 
 * 由于压缩和缓存策略通常于具体的存储殷勤实现相关，这里提供一个简单的模拟实例。
 */

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class CompressionCache {
private:
    unordered_map<string, string> cache; // 缓存存储
public:
    // 模拟数据压缩
    string compress(const string& data) {
        // 实际压缩逻辑
        return "(compressed) " + data; // return original data as e.g.
    }

    string decompress(const string& compressedData) {
        // actual decompress
        return "(decompressed) " + compressedData;
    }

    // saving data to cache
    void cacheData(const string& key, const string& data) {
        cache[key] = data;
    }

    // obtain cached data
    string getCachedData(const string& key) {
        if (cache.count(key)) {
            return cache[key];
        }
        return ""; // not hit cache. may need I/O
    }
};

int main() {
    /** 所以实际流程就是把数据压缩，然后和key一起存进cache。需要时从cache用key读取data，然后解压缩。 */
    CompressionCache cc;
    string originalData = "This is some data to compress.";
    string compressedData = cc.compress(originalData);
    cc.cacheData("key1", compressedData); // push key1 and data to cache.

    string cachedData = cc.getCachedData("key1");
    string decompressedData = cc.decompress(cachedData);

    cout << "Original data: " << originalData << endl;
    cout << "Decompressed Data: " << decompressedData << endl;
    return 0;
}

