#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <climits>

using namespace std;

#define pb push_back
#define sz(a) (int)a.size()
#define vi vector <int>
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for(int i = 1; i <= n; ++i)
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
const ll inf = 2ll*1e15;
const ll mod = inf + 7;
const ll N = 1e7;

bool isOneEditDistance(string& s, string& t) {
        if (s.size() > t.size())
            swap(s, t);
        bool ok = 1;
        for (int i = 0, j = 0; i < t.size(); ++i) {
            if (s[j] != t[i]) {
                if (!ok)
                    return false;
                ok = 0;
                if (s.size() == t.size())
                    j++;
            } else
                j++;
        }
        return !ok;
    }
bool isMatch(vector<string> &a, vector<string> &b) {
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i] && !isOneEditDistance(a[i], b[i]))
            return false;
    }
    return true;
}
bool bad(char c) {
    if (isalpha(c))
        return false;
    if (isdigit(c))
        return false;
    return true;
}

vector<string> spl(string s) {
    vector<string> spl;
    string str = "";
    for (char c : s) {
        if (bad(c)) {
            spl.push_back(str);
            str = "";
        } else {
            str += c;
        }
    }
    spl.push_back(str);
    vector<string> ans;
    str = "";
    for (char c : spl[0]) {
        if (c == ' ') {
            ans.push_back(str);
            str = "";
        } else {
            str += c;
        }
    }
    ans.push_back(spl[1]);
    return ans;
}
int main() {
	int n, m;
	cin >> n;
	vector<vector <string>> names, db;
	string s;
	forn(i, n) {
		std::vector<string> v(2);
		cin >> v[0] >> v[1];

		names.pb(v);	
	}
	cin >> m;
	getline(cin, s);
	forn(i, m) {
		getline(cin, s);
		auto k = spl(s);
		db.pb(k);
	}
	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < m; ++k) {
			if (isMatch(names[i], db[k]))
				return cout << db[k][2] << endl, 0;
		}
	}
}