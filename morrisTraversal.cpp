// https://leetcode.com/problems/binary-tree-preorder-traversal/solution/

vector<int> preorderTraversal(TreeNode* root) {
    vector <int> ans;
    TreeNode* node = root;
    while (node) {
        if (node->left) {
            TreeNode* child = node->left;
            while (child->right && child->right != node) {
                child = child->right;
            }
            if (!child->right) {
                child->right = node;
                ans.push_back(node->val);
                node = node->left;
            } else {
                child->right = NULL;
                node = node->right;
            }
            
        } else {
            ans.push_back(node->val);
            node = node->right;
        }
    }
    return ans;
}