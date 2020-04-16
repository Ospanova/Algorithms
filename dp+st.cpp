// https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/ - Minimum Cost Tree From Leaf Values

#include <iostream>
#include <vector>
using namespace std;


class SparseTable {
    public:
        SparseTable (int n, vector <int>& a);
        int GetMaxInRange(int l, int r);
    private:
        vector <int> lg_, nums_;
        vector <vector <int>> table_;
        int sz_;
        void PreCalc();
};


int SparseTable :: GetMaxInRange (int l, int r) {
    int len = r - l + 1;
    return max(table_[l][lg_[len]], table_[r - (1 << lg_[len]) + 1][lg_[len]]);
}


void SparseTable :: PreCalc() {
    for (int i = 0; i < sz_; ++i) { // initialization
        vector <int> cur (lg_[sz_] + 1, INT_MIN);
        table_.push_back(cur);
    }
    for (int i = 0; i < sz_; ++i) {
        table_[i][0] = nums_[i];
    }
    for (int j = 1; j <= lg_[sz_]; ++j) {
        for (int i = 0; i < sz_; ++i) {
            if (i + (1 << (j - 1)) >= sz_)
                break;
            table_[i][j] = max(table_[i][j - 1], 
                                table_[i + (1 << (j - 1))][j - 1]);
        }
    }
}

SparseTable :: SparseTable(int n, vector <int>& a) : sz_(n), nums_(a), lg_(n + 1) {
    lg_[1] = 0;
    for (int i = 2; i <= sz_; ++i)
        lg_[i] = lg_[i/2] + 1;
    PreCalc();
}


int mctFromLeafValues(vector<int>& arr) {
    // dp[i][j] => answer for [i:j] by dividing this tree into parts
    // dp[i][j] = min( dp[i][j], max([0:k))*max([k + 1:j)) + dp[i][k] + dp[k+1][j])
    int n = arr.size();
    SparseTable st = SparseTable(n, arr);
    vector <vector <int>> dp(n, vector <int>(n, 1e9));
    for (int i = 0; i < n; ++i) 
        dp[i][i] = arr[i];
    
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i < n; ++i) {
            int j = i + len - 1;
            if (j >= n)
                break;
            for (int k = i; k < j; ++k) { // cut after k
                dp[i][j] = min(st.GetMaxInRange(i, k)*st.GetMaxInRange(k + 1, j) + ((i != k) ? dp[i][k] : 0) +
                               (k + 1 != j ? dp[k + 1][j] : 0), dp[i][j]);
            }
        }
    }
    return dp[0][n - 1];
}
int main() {
	int n, x;
	vector <int> v;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> x, v.push_back(x);
	cout << mctFromLeafValues(v) << endl;
	return 0;
}