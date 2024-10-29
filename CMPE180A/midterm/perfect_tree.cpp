#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class PerfectTree {
public:
    int getDepth(TreeNode* root) {
        int dep = 0;
        TreeNode* curr = root;
        while (curr != nullptr && curr->left != nullptr) {
            curr = curr->left;
            dep++;
        }
        return dep;
    }

    bool isPerfect(TreeNode* root) {
        int depth = getDepth(root);
        return isPerfectTree(root, depth, 0);
    }

    bool isPerfectTree(TreeNode* root, int depth, int level) {
        if (root == nullptr) {
            return true;
        }

        if (root->left == nullptr && root->right == nullptr) {
            // this is a leaf
            return depth == level;
        }

        // noting this one! we cannot check this in next recursion.
        if (root->left == nullptr || root->right == nullptr) {
            return false;
        }

        return isPerfectTree(root->left, depth, level + 1) && isPerfectTree(root->right, depth, level + 1);
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    //root->right->right = new TreeNode(7);

    PerfectTree pt;
    if (pt.isPerfect(root)) {
        cout << "is perfect" << endl;
    } else {
        cout << "not perfect tree" << endl;
    }

    return 0;
}