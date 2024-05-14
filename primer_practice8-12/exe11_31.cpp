#include <iostream>
#include <string>
#include <vector>
#include <map>  // for both map and multimap
#include <set>
using namespace std;

/**
 * 编写程序，定义一个作者及其作品的multimap。
 * 使用find在multimap中查找一个元素并用erase删除它。
 * 确保你的程序在元素不在map 中时也能正常运行。
*/
void authorMap(multimap<string, string>& authors) {
    string author = "pezy";
    string work = "CP5";

    auto found = authors.find(author);
    auto count = authors.count(author);  // in both unordered_map, map and multimap
    // count is size_t, representing the frequency of key word in a map.
    while (count) {
        if (found->first == author) {
            authors.erase(found);
            break;
        }
        found++;  // iterator
        count--; // 
    }
    for (const auto& [author, word] : authors) {
        cout << author << ": " << word << endl;
    }
}

int main() {
    multimap<string, string> authors {
        {"alan", "DMA"},
        {"prezy", "Leetcode"},
        {"alan", "CLRS"},
        { "wang", "FTP" },
		{ "pezy", "CP5" },
		{ "wang", "CPP-Concurrency" } 
    };

    // copy map to sorted map first
    map<string, multiset<string>> sorted_authors;
    for (const auto& [key, val] : authors) {
        sorted_authors[key].insert(val);
    }

    // then erase key word
    authorMap(authors);

    for (const auto& [key, works] : sorted_authors) {
        cout << key << ": ";
        for (const auto& w : works) {
            cout << w << " ";
        }
        cout << endl;
    }

    return 0;
}
/**
alan: DMA
alan: CLRS
prezy: Leetcode
wang: FTP
wang: CPP-Concurrency

alan: CLRS DMA 
pezy: CP5 
prezy: Leetcode 
wang: CPP-Concurrency FTP 
*/