/** Rocksdb use specific data encoding format to serialize and deserialize key value pair
 * to support store and search
 */
#include <iostream>
#include <string>
using namespace std;

class DataEncoder {
public:
// mimic key value pair
    string encoder(const string& key, const string& value) {
        // 实际编码逻辑，例如，使用某种协议缓冲区或自定义格式
        // 这里简单地key value 拼接作为示例
        return key + ":" + value;
    }

    pair<string, string> decode(const string& encodeData) {
        // actual decode logic not shown here
        size_t pos = encodeData.find(":");
        string key = encodeData.substr(0, pos);
        string value = encodeData.substr(pos + 1);
        return {key, value};
    }
};

int main() {
    DataEncoder encoder;
    string key = "key1";
    string value = "value1";
    string encodeData = encoder.encoder(key, value);
    auto decodedData = encoder.decode(encodeData);

    cout << "Encoded Data: " << encodeData << endl;
    cout << "Decoded key: " << decodedData.first << ", Value: " << decodedData.second << endl;
    return 0;
}