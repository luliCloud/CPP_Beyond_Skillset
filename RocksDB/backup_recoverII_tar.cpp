#include <iostream>
#include <fstream>
#include <filesystem>
#include <archive.h>  // sudo apt-get install libarchive-dev
#include <archive_entry.h>
#include <vector>
using namespace std;

/** 数据恢复流程通常涉及从备份中提取数据并恢复到数据中 */
void restoreData(const string& backupFilePath, const string& restoreDir) {
    struct archive* a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_compression_all(a);  // 使用所有支持的压缩格式
    archive_read_open_filename(a, backupFilePath.c_str(), 512);

    struct archive_entry* entry;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* pathname = archive_entry_pathname(entry);
        string filename = restoreDir + '/' + pathname;
        // 创建目录结构
        filesystem::create_directories(filesystem::path(filename).parent_path());

        // extract file
        ofstream outFile(filename, ios::binary);
        const void* buff;
        size_t bytesRead;
        int64_t offset;
        while (true) {
            int r = archive_read_data_block(a, &buff, &bytesRead, &offset);
            if (r == ARCHIVE_EOF) {
                break;
            }
            if (r < ARCHIVE_OK) {
                cerr << "Error reading data block: " << archive_error_string(a) << endl;
            }
            outFile.write(static_cast<const char*>(buff), bytesRead);
        }
        outFile.close();
        archive_entry_clear(entry);
    }
    archive_read_free(a);
}

int main() {
    const string backupFilePath = "backup.tar";
    const string restoreDir = "restore"; // the dir store all recovered files
    restoreData(backupFilePath, restoreDir);
    return 0;
}
/**
 * g++ -std=c++17 -I./rocksdb/include -L./rocksdb backup_recoverII_tar.cpp -larchive
 */