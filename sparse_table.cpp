#include <iostream>
#include <vector>

using namespace std;

class node {
public:
	int ind, depth;
	node(int ind, int h) : ind(ind), depth(h) {}
	void print() {
		cout << depth << " " << ind << endl;
	}
};
class SparseTable {
private:
	vector <node> array;
	vector <vector <node>> table;
	int log[1000*1000];
public:
	SparseTable(vector <node> array){
		int n = array.size();
		log[1] = 0;
		for (int i = 2; i <= n; ++i) 
			log[i] = log[i/2] + 1;
		for (int i = 0; i < n; ++i){
			vector <node> cur(log[n] + 1, {0,0});
			table.push_back(cur);
		}
		for (int i = 0; i < n; ++i)
			table[i][0] = array[i];
		for (int l = 1; l <= log[n]; ++l) {
			for (int i = 0; i < n; ++i) {
				/*
					chaeck for valid
				*/ 
				if (i + (1 << (l - 1)) < n)
					table[i][l] = getMin(table[i][l - 1], 
					          table[i + (1 << (l - 1))][l - 1]);
				else
					table[i][l] = table[i][l - 1];
			}
		}
	}
	node getMin(node& a, node& b) {
		if (a.depth < b.depth)
			return a;
		return b;
	}
	
	node getLCA(int l, int r) {
		int len = r - l + 1;
		/*
			+ 1 for another part
		*/
		node cur = getMin(table[l][log[len]],table[r - (1 << log[len]) + 1][log[len]]);
		return cur;
	}
};

void dfs(int v, vector <int>& lvl, vector <int>& pos,
         vector <node>& path, vector <vector<int>>& graph) {
	// cout << v  << endl;
	if (pos[v] == -1)
		pos[v] = path.size();
	path.push_back({v, lvl[v]});
	for (int to : graph[v])
		if (lvl[to] == 0) {
			lvl[to] = lvl[v] + 1;
			dfs(to, lvl, pos, path, graph);
			path.push_back({v, lvl[v]});
		}
}


int main() {
	
	int n;
	cin >> n;
	vector <vector <int>> graph(n + 1);
	for (int i = 1, x, y; i <= n - 1; ++i) {
		cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
	}
	vector <int> pos(n + 1, -1);
	vector <int> lvl(n + 1, 0);
	vector <node> path;
	lvl[1] = 1;
	dfs(1, lvl, pos, path, graph);

	SparseTable st = SparseTable(path);

	int q;
	cin >> q;
	for (int i = 0, a, b; i < q; ++i) {
		cin >> a >> b;
		node lca = st.getLCA(min(pos[a], pos[b]), max(pos[b], pos[a]));
		cout << "LCA for " << a << " and " << b << " is " << lca.ind << endl;
	}
}
