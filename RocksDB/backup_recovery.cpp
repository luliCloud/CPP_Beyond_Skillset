/** 备份与恢复是确保数据库在面临数据丢失或者系统故障时能够快速恢复正常运行的关键策略
 * 数据备份策略通常包括全量备份，增量备份和差异备份
 */
#include <iostream>
#include <fstream>
#include <filesystem>
#include <archive.h>  // sudo apt-get install libarchive-dev
#include <archive_entry.h>
#include <vector>
using namespace std;

void addFileToArchive(struct archive* a, const filesystem::path& filePath) {
    struct archive_entry* entry = archive_entry_new();
    archive_entry_set_pathname(entry, filePath.string().c_str());
    archive_entry_set_size(entry, filesystem::file_size(filePath)); // file size
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);
    archive_write_header(a, entry);

    ifstream file(filePath, ios::binary);
    if (file) {
        vector<char> buffer(1024);
        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
            archive_write_data(a, buffer.data(), file.gcount());
        }
    }
    archive_entry_free(entry);
}

void backupData(const string& sourceDir, const char* backupFilePath) {
    /** 使用了 libarchive 库来创建一个新的归档文件，并将输出设置为特定文件路径。 */
    struct archive* a = archive_write_new();
    archive_write_set_format_pax_restricted(a); // use PAX format
    int r;
    r = archive_write_open_filename(a, backupFilePath);
    if (r != ARCHIVE_OK) {
        cerr << "Error opening archive file: " << archive_error_string(a) << endl;
        archive_write_free(a);
        return;
    }

    // 遍历目录并添加文件到归档
    for (const auto& dirEntry : filesystem::recursive_directory_iterator(sourceDir)) {
        if (dirEntry.is_regular_file()) {
            addFileToArchive(a, dirEntry.path());
        }
    }

    archive_write_close(a);
    archive_write_free(a);
}

int main() {
    const char* backupFilePath = "backup.tar";
    string sourceDir = "backup_example";  // 直接进dir，不需要/

    backupData(sourceDir, backupFilePath);
    cout << "Backup create at " << backupFilePath << endl;
    return 0;
}
/**
 * g++ -std=c++17 -I./rocksdb/include -L./rocksdb backup_recovery.cpp -larchive
 */