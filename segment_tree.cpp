// https://leetcode.com/problems/online-majority-element-in-subarray/

class MajorityChecker {
public:
    class Pair {
    public:
        int val, cnt;
        Pair (int val, int cnt) : val(val), cnt(cnt) {
        }
        Pair operator * (const Pair pair) {
            if (val == pair.val) 
                return Pair (val, cnt + pair.cnt);
            if (pair.cnt > cnt)
                return Pair (pair.val, pair.cnt - cnt);
            return Pair (val, cnt - pair.cnt);
        }
    };
    class SegmentTreeNode {
    public:
        int l, r;
        SegmentTreeNode* left;
        SegmentTreeNode* right;
        Pair data;
        SegmentTreeNode(int l, int r, Pair data) : l(l), r(r), data(data) {
        }
    };
    class SegmentTree {
        public:
        SegmentTree(vector <int>& nums) {
            root = build(0, nums.size() - 1, nums);
        }
        Pair getQuery(int l, int r) {
            return getMajority(root, l, r);
        }
    private:
        SegmentTreeNode* root;
        SegmentTreeNode* build (int l, int r, vector <int> nums) {
            if (l == r) {
                return new SegmentTreeNode(l, r, Pair(nums[l], 1));
            }
            auto curNode = new SegmentTreeNode(l, r, Pair(0, 0));
            int mid = l + (r - l)/2;
            curNode->left = build(l, mid, nums);
            curNode->right = build(mid + 1, r, nums);
            curNode->data = curNode->left->data*curNode->right->data;
            return curNode;
        }
        Pair getMajority(SegmentTreeNode* cur, int l, int r) {
            if (cur->l == l && cur->r == r) 
                return cur->data;
            int mid = cur->l + (cur->r - cur->l)/2;
            if (mid >= r) return getMajority(cur->left, l, r);
            if (mid < l) return getMajority(cur->right, l, r);
            return getMajority(cur->left, l, mid)*getMajority(cur->right, mid + 1, r);
        }
    };
    MajorityChecker(vector<int>& arr) {
        tree = new SegmentTree(arr);
        for(int i = 0;i < arr.size(); ++i){
            indexes[arr[i]].push_back(i);
        }
    }
    
    int query(int left, int right, int threshold) {
        auto ans = tree->getQuery(left, right);
        if (ans.cnt >= threshold)
            return ans.val;
        
        auto inds = indexes[ans.val];
        auto l_id = lower_bound(inds.begin(), inds.end(), left);
        auto r_id = upper_bound(inds.begin(), inds.end(), right);
        if (r_id - l_id >= threshold)
            return ans.val;
        return -1;
    }
    SegmentTree* tree;
    unordered_map <int, vector <int>> indexes;
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */