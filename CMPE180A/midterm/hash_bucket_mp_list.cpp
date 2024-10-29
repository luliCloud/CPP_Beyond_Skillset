#include <iostream>
#include <utility> // for pair
#include <list>
#include <vector>
#include <functional>  // for hash function
using namespace std;

// implement a hash table using vector and list
class HashTable {
public:
    HashTable(int n) {
        size = n;
        // remember this!
        hashTable.resize(n);
    }

    int hash(int key) const {
        return std::hash<int>{}(key) % size; // can using key % size, though too simple
    }

    bool insert(int key, int val) {
        int idx = hash(key);
        for (auto& kv : hashTable[idx]) { // iterate the list
            if (kv.first == key) {
                kv.second = val;
                return false;
            }
        }
        // don't forget here
        hashTable[idx].push_back({key, val});
        return true;
    }

    bool remove(int key) {
        int idx = hash(key);
        for (auto it = hashTable[idx].begin(); it != hashTable[idx].end(); it++) {
            if (it->first == key) {
                hashTable[idx].erase(it);
                
                return true;
            }
        }
        return false;
    }

    bool find(int key, int& value) const {
        // return val, other wise return -1? . or return true and false
        int idx = hash(key);
        for (auto& kv : hashTable[idx]) {
            if (kv.first == key) {
                value = kv.second;
                return true;
            }
        }

        return false;
    }

    void display() const {
        for (size_t i = 0; i < hashTable.size(); ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& kv : hashTable[i]) {
                std::cout << "[" << kv.first << ": " << kv.second << "] ";
            }
            std::cout << "\n";
        }
    }

private:
    vector<list<pair<int, int>>> hashTable; // idx->list of pair {key, val}
    int size;
};

int main() {
    HashTable hashTable(10);

    hashTable.insert(1, 10);
    hashTable.insert(2, 20);
    hashTable.insert(3, 30);
    hashTable.insert(4, 40); // Updates the value for "apple"

    int value;
    if (hashTable.find(1, value)) {
        std::cout << "Found 1: " << value << "\n";
    } else {
        std::cout << "1 not found.\n";
    }

    hashTable.display();

    hashTable.remove(1);
    std::cout << "After removing 1:\n";
    hashTable.display();

    return 0;

}

