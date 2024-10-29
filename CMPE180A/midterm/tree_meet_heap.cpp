#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// check structural property
bool isStructuralComplete(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }

    queue<TreeNode*> q;
    bool end = false;

    q.push(root);
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (!end) {
            if (curr == nullptr) {
                end = true;
            } else {
                q.push(curr->left);
                q.push(curr->right);
            }
        } else {
            if (curr != nullptr) {
                return false;
            }
        }
    }
    return true;
}

// check maxheap order property
bool isHeapOrder(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr->left != nullptr && curr->left->val > curr->val) { // can be ==
            return false;
        } else if (curr->left != nullptr) {
            q.push(curr->left);
        } 

        if (curr->right != nullptr) {
            if (curr->right->val > curr->val) {
                return false;
            } else {
                q.push(curr->right);
            }
        }
    }
    return true;
}

int main() {
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(6);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(4);
    //root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(1);

    bool res = isStructuralComplete(root);
    res = res && isHeapOrder(root);
    if (res) {
        cout << "is max heap" << endl;
    } else {
        cout << "not max heap" << endl;
    }

    return 0;
}

