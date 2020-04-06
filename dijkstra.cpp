// https://codeforces.com/contest/545/problem/E


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

vector <long long> dijkstra(const int& s, int n, const vector <vector <pair <int, pair <int, int>>>>& g,
							vector <long long>* p) {

	vector <long long> d(n + 1, INF);
	priority_queue <pair<long long, int>> q;

	d[s] = 0;
	q.push({0, s});
	while (!q.empty()) {
		long long cur = q.top().second, cur_d = (-1)*q.top().first;
		q.pop();

		if (cur_d > d[cur])  continue;

		for (auto nei : g[cur]) {
			long long to = nei.second.first, cost = nei.second.second;
			if (d[to] >= cur_d + cost) {

				if (d[to] > cur_d + cost)
					q.push({-cur_d - cost, to});

				d[to] = cur_d + cost;
				(*p)[to] = nei.first;
			}
		}
	}
	return d;
}

int main() {

	int n, m, u;
	cin >> n >> m;
	vector <vector <pair <int, pair <int, int>>>> g(n + 1);
	vector<long long> parent(n + 1, -1), w(m + 1, 0), used(m + 1, 0);
	long long ans = 0;

	for (long long i = 0, a, b, x; i < m; ++i) {
		cin >> a >> b >> x;
		g[a].push_back({i, {b, x}});
		g[b].push_back({i, {a, x}});
		w[i] = x;
	}
	cin >> u;

	auto d = dijkstra(u, n, g, &parent);
	
	for (int i = 1; i <= n; ++i) 
		if(i != u) {
			ans += w[parent[i]];
			used[parent[i]] = 1;
		}

	cout << ans << endl;
	for (auto i = 0; i < m; ++i) {
		if (used[i])
			cout << i + 1 << " ";
	}
	cout << endl;
}