#include <vector>
#include <iostream>
#include <fstream> // read file
#include <sstream>
#include <string>
#include <stdexcept> // for exceptions like invalid_argument, out_of_range
using namespace std;

bool file_read_matrix(fstream& f, vector<vector<int>>& ma, int& row, int& col);
bool file_read_vector(fstream& f, vector<int>& ve, int& sz);

int main (int argc, char** argv) {
    if (argc != 5) {
        cerr << "Please input as the following format: ./a.out -m matrix.txt -v vector.txt" << endl;
        return 1;
    }

    string file1, file2;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-m" && i + 1 < argc) {
            i++;
            file1 = argv[i];
        } else if (string(argv[i]) == "-v" && i + 1 < argc) {
            i++;
            file2 = argv[i];
        } else {
            cerr << "Invalid input" << endl;
            return 1;
        }
    }

    if (file1.empty() || file2.empty()) {
        cerr << "No file name" << endl;
        return 1;
    }

    fstream f1, f2;
    f1.open(file1, ios::in);
    if (!f1.is_open()) {
        cerr << "The file " << file1 << "cannot be opened" << endl;
        return 1;
    }
    f2.open(file2, ios::in);
    if (!f2.is_open()) {
        cerr << "The file " << file2 << "cannot be opened" << endl;
        return 1;
    }

    vector<vector<int>> ma; 
    vector<int> ve;
    int row = 0, col = 0, sz = 0;
    bool status1 = file_read_matrix(f1, ma, row, col);
    if (!status1) {
        cerr << "Read failures due to non-number input" << endl;
        return 1;
    }
    bool status2 = file_read_vector(f2, ve, sz);
    if (!status2) {
        cerr << "Read failures due to non-number input" << endl;
        return 1;
    }
    // check whether matrix col num match vector size
    if (col != sz) {
        cout << "The colume number " << col << " in matrix does not match vector size " 
        << sz << endl;
        return 0;
    }

    for (int i = 0; i < row; i++) {
        int res = 0;
        for (int j = 0; j < col; j++) {
            res += ma[i][j] * ve[j];
        }
        cout << res << endl;
    }
    return 0;
}

// noting f need to be changed when read, i.e. file ptr position. not const
bool file_read_matrix(fstream& f, vector<vector<int>>& matrix, int& row, int& col) {
    string line;
    
    if (getline(f, line)) {
        istringstream iss(line);
        string r, c;
        iss >> r >> c;

        row = atoi(r.c_str());
        col = atoi(c.c_str());
    }
    for (int i = 0; i < row; i++) {
        if (!getline(f, line)) {
            return false;
        }
        
        vector<int> row;
        istringstream iss(line);
        string num;

        for (int j = 0; j < col; j++) {
            iss >> num;
            try {
                int n = stoi(num);  // atoi not throw exception
                row.push_back(n);
            } catch (const invalid_argument& e) {  // not number
                return false;
            } catch (const out_of_range& e) {
                return false;
            }
        }
        matrix.push_back(row);
    }
    return true;
}

bool file_read_vector(fstream& f, vector<int>& ve, int& sz) {
    string line;
    
    if (getline(f, line)) {
        istringstream iss(line);
        string s;
        iss >> s;

        sz = atoi(s.c_str());
    }

    for (int i = 0; i < sz; i++) {
        if (!getline(f, line)) {
            return false;
        }
        istringstream iss(line);
        string num;

        while (iss >> num) {
            try {
                int n = stoi(num);
                ve.push_back(n);
            } catch (invalid_argument) {  // not number
                return false;
            } catch (out_of_range) {
                return false;
            }    
        }
    }
    return true;
}