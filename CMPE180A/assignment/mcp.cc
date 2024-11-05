#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set> // store target files
using namespace std;

void copy_content(ifstream& source_stream, const string& target_file);

int main(int argc, char** argv) {
    if (argc < 5 || argc % 2 == 0) {
        cerr << "Input arguments are missing." << endl;
        cerr << "Usage: mcp -s source_file_name -t target_file_name [-t target_file_name_x ...]" << endl;
        return 1;
    }

    string source_file;
    unordered_set<string> target_file;

    // read input
    for (int i = 1; i < argc; i += 2) {
        if (string(argv[i]) == "-s" && (i % 2 == 1) && i + 1 < argc) {
            source_file = string(argv[i + 1]);
        } else if (string(argv[i]) == "-t" && (i % 2 == 1) && i + 1 < argc) {
            if (target_file.count(string(argv[i + 1]))) {
                cerr << "Duplicated target file name is not allowed." << endl;
                return 1;
            }  else {
                target_file.insert(string(argv[i + 1]));
            }
        } else {
            cerr << "Invalid input: Usage: mcp -s source_file_name -t target_file_name [-t target_file_name_x ...]" << endl;
            return 1;
        }
    }

    if (source_file.empty() || target_file.empty()) {
        cerr << "No source file or target file given: Usage: mcp -s source_file_name -t target_file_name [-t target_file_name_x ...]" << endl;
        return 1;
    }

    // check if target files exist
    for (const string& tf : target_file) {
        ifstream target_stream(tf, ios::binary);
        if (target_stream) { // can open then it exist
            cerr << "Target file " << tf << " already exist. Cannot be written" << endl;
            return 1;
        }
    }

    // open source file. 
    // using binary mode to open the source file, so that both text file and binary file can be copied
    ifstream source_stream(source_file, ios::binary); // ifstream is to read
    if (!source_stream) {
        cerr << "Source file " << source_file << " opened failed (not exist)" << endl;
        return 1;
    }

    // copy cocent 
    for (const string& tf : target_file) {
        // clear the label or other status bit, like EOF
        source_stream.clear();

        // finish the last read and move the read ptr go back to the begnning
        source_stream.seekg(0, ios::beg);
        copy_content(source_stream, tf);
    }

    source_stream.close();
    return 0;
}

void copy_content(ifstream& source_stream, const string& target_file) {
    ofstream target_stream(target_file, ios::binary); // ofstream is to write
    if (!target_stream) {
        cerr << "Target file " << target_file << "createed failed" << endl;
        exit(1);
    }

    target_stream << source_stream.rdbuf(); // using rdbuf to copy all content
    target_stream.close();
}

/**
 * ./a.out -s test1 -t copy -t copy1 -t copy2
 */