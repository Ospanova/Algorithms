// https://atcoder.jp/contests/dp/tasks/dp_g - Find longest path

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


void dfs(int v, vector <bool>& used, vector <vector <int>>& g, vector <int>& order) {
	used[v] = 1;
	for (int to: g[v])
		if (!used[to])
			dfs(to, used, g, order);
	order.push_back(v);
}


int getMaxPathLenght(int n, vector <vector <int>>& edges) {
	vector <vector <int>> g(n + 1), inv(n + 1);
	vector<int> order, dp(n + 1, 0);
	vector <bool> used(n + 1, 0);
	int ans = 0;

	for (auto& edge : edges) {
		g[edge[0]].push_back(edge[1]);
		inv[edge[1]].push_back(edge[0]);
	}
	
	for (int i = 1; i <= n; ++i)
		if (!used[i])
			dfs(i, used, g, order);


	for (int i = 0; i < n ; ++i) {
		for (int from : inv[order[i]]) 
			dp[from] = max(dp[from], 1 + dp[order[i]]);
		
		ans = max(ans, dp[order[i]]);
	}

	return ans;
}


int main() {
	int n, m, a, b;
	cin >> n >> m;
	vector <vector <int>> edges;
	for(int i = 0; i < m; ++i)
		cin >> a >> b, edges.push_back({a, b});
	cout << getMaxPathLenght(n, edges) << endl;
	return 0;
}