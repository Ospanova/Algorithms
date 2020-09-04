#include <iostream> 

using namespace std;


int a, b;

const double EPS = 1e6;

int f(int x) {
	return  (x + min((a - 2*x), (b - x)/2));
}


int ternarySearchMaxInt(int l, int r) {
	// try to find max value of function
	while (l + 3 < r) {
		int m1 = (2*l + r) / 3;
		int m2 = (l + 2*r) / 3;
		if (f(m1) <= f(m2)) {
			l = m1;
		} else {
			r = m2;
		}
	}
	int mx = f(l++);
	while (l <= r)
		mx = max(mx, f(l++));
	return mx;
}

double ternarySearchMaxDouble(double l, double r) {
	while (r - l > EPS) {
		double m1 = (2*l + r) / 3;
		double m2 = (l + 2*r) / 3;
		if (f(m1) <= f(m2)) {
			l = m1;
		} else {
			r = m2;
		}
	}
	return f(l);
}

int solve() {	
	cin >> a >> b;
	int l = 0, r = max(min(a/2, b), min(b/2, a)); 
	return ternarySearchMaxInt(l, r);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); 

	int t;
	cin >> t;
	while (t--) {
		cout << solve() << endl;
	}
}
