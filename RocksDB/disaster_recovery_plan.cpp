#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <archive.h>
#include <archive_entry.h>
using namespace std;

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

void disasterRecoveryPlan(const string& backupDir, const string& systemStateFile) {
    // check system state file, ensure recovery point
    ifstream stateFile(systemStateFile);
    if (!stateFile.is_open()) {
        cerr << "Failed to open system state file." << endl;
        return;
    }
    string lastBackupTime;
    getline(stateFile, lastBackupTime);
    stateFile.close();

    // based on last backup time to backup file
    filesystem::path backupPath = backupDir;
    for (const auto& entry : filesystem::directory_iterator(backupPath)) {
        if (entry.path().filename().string().find(lastBackupTime) != string::npos) {
            // find the matching backup file
            string backupFile = entry.path().string();
            // execute recovery option
            restoreData(backupFile, "restore");  // from what we write before
            break;
        }
    }
}

int main() {
    const string backupDir = "backup.tar";
    const string systemStateFile = "system.state";
    disasterRecoveryPlan(backupDir, systemStateFile);
    return 0;
}

/** noting cannot run, as we don't really create a system file */
