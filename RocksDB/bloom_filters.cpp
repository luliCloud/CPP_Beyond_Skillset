/**
 * Bloom Filter 是一种空间效率很高的概率型数据结构，用于判断一个元素是否在一个集合中。
 * RocksDB为每个SSTable维护一个bloom filter，以减少不必要的磁盘I/O
 */
#include <iostream>
#include <bitset>
#include <functional>
using namespace std;

class BloomFilter {
private:
    bitset<100> bs; // 位数组，这里简化为100位。每一个位置是一个位数组。当一个key存进来时
    // 会对应X个hash func，然后会分别跟一个100位的base 位数intersect，最后得到这个key 的一个位数
    // 所以当一个key进来，可以直接查。如果不存在这个位数，一定就是不存在。如果有相同的位数，就有可能在这个
    // sstable里。为什么空间利用率很高呢，因为100位数也就是100个0/1而已。所以也就是100bit，
    // 大约13 bytes。但是original value可能是很长很大的，所以它通过位运算，位数和哈希（稳定计算时间），
    // 极大的节省了空间和时间。
    // 使用所有的哈希函数对字符串进行哈希，并在 bitset 的对应位置设置为 true。所以查找一个数字就可以
    // 看到这个100位数组的有没有刚好有一个mode和数字hash出来的位数对应上
    // 注意位数组不是一个size为所有插入数字的大小的set，而是有100 就是100个位数的集合。
    vector<function<unsigned int(string)>> hashFuncs; // 哈希函数集合。接收string， 返回int
public:
    BloomFilter() {
        // initialize hashfunc
        /**
         * [this]表示lambda表达式补货当前对象的this指针，使得lambda表达式可以访问对象的member&func
         * 参数列表（string s）：这个lambda表达式接收一个参数s。
         * 函数体：使用标准库的std：：hash对字符串s进行哈希计算。将得到的哈希值mod bitset 的大小。
         * hash<string> 指定我们要使用的hash模版累，且模版参数是string
         * {}：使用统一初始化语法创建一个临时的 std::hash<string> 对象。（s）调用这个临时对象的
         * operator（）方法，并传入参数s。
         */
        hashFuncs.push_back([this](string s) {
            return hash<string>{}(s) % bs.size();
        });
        // 可以添加更多的哈希函数
    }

    /** 添加元素到bloom filter */
    void add(string element) {
        for (auto& hashFunc : hashFuncs) {
            bs.set(hashFunc(element)); //  将哈希值对应位设为1
        }
    }

    /** 判断元素是否可能存在于bloom filter */
    bool mightContain(string element) {
        for (auto& hashFunc : hashFuncs) {
            if (!bs.test(hashFunc(element))) {
                return false; // 有一个位为0，则元素一定不在集合中
            }
        }
        return true; // 所有位都为1，则元素可能在集合中
    }
};

int main() {
    BloomFilter bloomfilter;
    bloomfilter.add("key1");
    bloomfilter.add("key2");

    cout << "key1 might be in the set (1 is exist):" << bloomfilter.mightContain("key1") << endl;
    cout << "key3 might be in the set: " << bloomfilter.mightContain("key3") << endl;
    return 0;
}