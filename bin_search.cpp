//Aggressive cows - https://www.spoj.com/problems/AGGRCOW/

#include <iostream>
#include <algorithm>

#define ll long long

using namespace std;

ll n, c;
int stalls[111111];

bool isValid (ll x) {
	ll cnt = 1, cur = 0;
	for (int i = 1; i < n; ++i) {
		cur += stalls[i] - stalls[i - 1];
		if (cur >= x)
			cur =  0, cnt++;
	}
	return cnt >= c;
}

void solve() {
	cin >> n >> c;
	for (int i = 0; i < n; ++i)
		cin >> stalls[i];
	sort(stalls, stalls + n);
	ll l = 1, r = 1e11;
	while (r - l > 1) {
		ll mid = l + (r - l)/2;
		if (isValid(mid))
			l = mid;
		else
			r = mid;
	}
	cout << l << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--)
		solve();
}