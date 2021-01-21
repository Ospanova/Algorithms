// https://codeforces.com/contest/1471/problem/D

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define pb push_back
#define sz(a) (int)a.size()
#define vi vector <int>
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for(int i = 0; i < n; ++i)
#define F first
#define S second
#define ll  long long
// typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

// const ll inf = 1e9;
const double eps = 1e-9;
const double pi = acos(-1.0);
const int SZ = 55555;
const ll inf = 1e9;
const ll mod = inf + 7;
const int N = 1e6;
int cnt[1111111];
vector <vector <int>> fact(N + 1);
void solve() {
	int n, x;
	cin >> n;
	unordered_map <int, int> cnt;
	forn(i, n) {
		cin >> x;
		int mask = 1, a = x;
		for (int del : fact[a]) {
			int degree = 0;
			while (x % del == 0) {
				x/=del;
				degree++;
			}
			if (degree & 1) {
				mask *= del;
			}
		}
		cnt[mask]++;
	}
	int secondAns = 0, ansMax = 0;
	for (auto i : cnt) {
		ansMax = max(ansMax, i.second);
		if (i.second % 2 == 0 || i.first == 1)
			secondAns += i.second;
	}
	int q;
	ll w;
	cin >> q;
	forn(i, q) {
		cin  >> w;
		if (w == 0)
			cout << ansMax << endl;
		else 
			cout << max(ansMax, secondAns) << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for (int i = 2; i <= N; ++i) {
		if (fact[i].empty()) {
			for (int x = i; x <= N; x += i) {
				fact[x].pb(i);
			}
		}
	}
	int q;
	cin >> q;
	while (q--) {
		solve();
	}
}