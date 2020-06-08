// Given a directed graph, return minimum of edges to keep all paths .

#include <iostream>
#include <vector>

using namespace std;


void dfs(int v, const vector <vector<int>>& g, vector <bool>* visited,
	     vector <int>* order = nullptr) {
	(*visited)[v] = true;
	for (int to : g[v]) {
		if ((*visited)[v] == 0)
			dfs(to, g, visited);
	}
	if (order != nullptr) 
		order->emplace_back(v);
}

int getEdgesToRemove(const vector <vector <int>>& edges, const int nodes) {
	vector <vector <int>> g(nodes + 1), reversedG(nodes + 1);
	int edges_number = edges.size();
	for (auto& edge : edges) {
		g[edge[0]].emplace_back(edge[1]);
		reversedG[edge[1]].emplace_back(edge[0]);
	}

	vector <bool> visited(nodes + 1);
	vector <int> order; // enter to sc components by this order:
						// the edge between comp. from c1 to c2, 
						// if tout[c1] > tout[c2]
	for (int i = 1; i <= nodes; ++i) {
		if (!visited[i])
			dfs(i, g, &visited, &order);
	}
	visited.resize(nodes + 1, 0);
	int components = 0;
	for (int i = nodes - 1; i >= 0; --i) {
		if (visited[order[i]] == 0) {
			dfs(order[i], reversedG, &visited);
			++components;
		}
	}
	return edges_number - components - nodes + 1;
}

int main() {
	vector <vector <int>> edges;
	int n, e;
	cin >> n >> e;
	for (int i = 0, a, b; i < e; ++i)
		cin >> a >> b, edges.push_back({a, b});
	cout << getEdgesToRemove(edges, n) << endl;
}