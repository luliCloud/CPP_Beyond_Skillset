#ifndef EX12_27_H
#define EX12_27_H
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
class QueryResult;

class TextQuery {
public: 
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string& s) const;
private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;  // line_no should be idx in vector<string>?
};

class QueryResult{
public: 
    friend ostream& print(ostream&, const QueryResult&);
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>> p,
                shared_ptr<vector<string>> f) :
                sought(s), lines(p), files(f) {}
private:
    string sought;
    shared_ptr<set<TextQuery::line_no>> lines;
    shared_ptr<vector<string>> files;
};

ostream& print(ostream&, const QueryResult&); // all prototype need to be claimed in h file
#endif
