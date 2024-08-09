#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_map>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int key, value;
    Node(Node* p, Node* n, int k, int v) : prev(p), next(n), key(k), value(v) {}
    Node(int k, int v) : prev(nullptr), next(nullptr), key(k), value(v) {}
};

class Cache {
protected:  // only child can get
    unordered_map<int, Node*> mp;
    int cp;
    Node* head;
    Node* tail;
    
    virtual void set(int, int) = 0;  // 指定这个函数为纯虚函数，没有实现。必须由它的派生类实现
    virtual int get(int) = 0;
};

class LRUCache : public Cache {
public:
    int size;
    LRUCache(int M) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
        cp = M;
        size = 0;
    }
    
    virtual void set(int k, int v) {
        if (mp.count(k)) {
            // change value of Node
            Node* curr = mp[k];
            curr->value = v;
            // move to head
            mp[k] = head->next; // update the corresponding position
        } else {
            if (size == cp) {
                // remove the last node
                int deleteKey = tail->prev->key;
                Node* deleteNode = tail->prev;
                tail->prev = deleteNode->prev;
                deleteNode->prev->next = deleteNode->next;
                mp.erase(deleteKey);
                delete deleteNode;
                
                size--;
            }
            size++;
            Node* curr = new Node(k, v);
            head->next->prev = curr;
            curr->next = head->next;
            head->next = curr;
            curr->prev = head;
            mp[k] = head->next;
        }
    }
    
    virtual int get(int k) {
        if (!mp.count(k)) {
            return -1;
        }
        moveHead(mp[k]);
        mp[k] = head->next;  // remember this
        return mp[k]->value;
    }
    
    void moveHead(Node* node) {
        // cut the prev and next of curr node
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        head->next->prev = node;
        node->next = head->next;
        head->next = node;
        node->prev = head;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, M;
    cin >> N >> M;
    
    LRUCache lru(M);
    while (N--) {
        string command;
        cin >> command;
        if (command == "set") {
            int k, v;
            cin >> k>> v;
            lru.set(k, v);
        } else {
            int k;
            cin >> k;
            int val = lru.get(k);
            cout << val << endl;
        }
    }   
    return 0;
}
