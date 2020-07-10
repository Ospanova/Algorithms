// https://leetcode.com/problems/two-sum-bsts/
//Time - O(n), Space - O(h)


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    template <typename T>
    class TreeIterator {
    private:
        vector<pair<T, bool>> stack_;
        T cur_;
        bool asc_;
    public:
        TreeIterator(T root, bool asc) : asc_(asc), stack_{{root, false}}, cur_() {
            ++(*this);
        }
        TreeIterator& operator++() {
            while (!stack_.empty()) {
                T root; 
                bool isVisited;
                tie(root, isVisited) = stack_.back();
                stack_.pop_back();
                if (!root) 
                    continue;
                if (isVisited) {
                    cur_ = root;
                    return *this;
                }
                if (asc_) {
                    stack_.emplace_back(root->right, false); // because we need to  firstly consider left
                    stack_.emplace_back(root, true);
                    stack_.emplace_back(root->left, false);
                } else {
                    stack_.push_back({root->left, false});
                    stack_.push_back({root, true});
                    stack_.push_back({root->right, false});
                }
            }
            cur_ = T();
            return *this;
        }
        const T& operator*() const {
            return cur_;
        }
    };
    
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        TreeIterator <TreeNode*> treeASC(root1, true), treeDESC(root2, false);
        while(*treeASC && *treeDESC) {
            if ((*treeASC)->val + (*treeDESC)->val < target)
                ++treeASC;
            else if ((*treeASC)->val + (*treeDESC)->val > target)
                ++treeDESC;
            else
                return true;
        }
        return false;
    }
};