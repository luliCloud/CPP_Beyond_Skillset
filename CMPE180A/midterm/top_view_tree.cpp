#include <iostream>
#include <vector>
#include <map> // using map, as we wnat start from the first col
#include <queue>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class TopView {
public:
    
    /** 用col的方式思考。任何在一列的第一个出现的val就是top view. should not put struct on private, otherwise inaccessible */
    vector<int> topView(Node* root) {
        if (root == nullptr) {
            return {};
        }

        vector<int> res;
        queue<pair<Node*, int>> q; // {val, col}
        q.push({root, 0}); // left -1, right + 1

        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            if (!mp.count(p.second)) {
                mp[p.second] = p.first;
            }
            if (p.first->left != nullptr) {
                q.push({p.first->left, p.second - 1});
            }
            if (p.first->right != nullptr) {
                q.push({p.first->right, p.second + 1});
            }
        }
        for (auto [k, node] : mp) {
            res.push_back(node->val);
        }
        return res;
    }
private:
    map<int, Node*> mp; // col->first ele

};

int main() {
    Node* root = new Node(7);
    root->left = new Node(6);
    root->right = new Node(5);
    root->left->left = new Node(4);
    //root->left->right = new TreeNode(3);
    root->right->left = new Node(2);
    root->right->right = new Node(1);
    TopView tv;

    vector<int> res = tv.topView(root);
    for (int r : res) {
        cout << r << " ";
    }
    cout << endl;
    return 0;
}



