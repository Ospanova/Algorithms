// K-based Numbers. Version 2 - https://acm.timus.ru/problem.aspx?space=1&num=1012 

#include <iostream>

using namespace std;

class BigInt {
	string number;
public:
	BigInt() : number("0") {}
	BigInt(string number) : number(number) {}
	BigInt operator+(const BigInt& other) {
		string a = number, b = other.number;
		int carry = 0, n = a.size(), m = b.size();
		if (n < m)
			swap(a, b), swap(n, m);
		int f = n - 1, s = m - 1, cur;
		while (s >= 0) {
			cur = a[f] + b[s] - 2*('0') + carry;
			a[f] = char(cur%10 + '0');
			carry = cur/10;
			f--, s--;
		}
		while (f >= 0) {
			cur = (a[f] - '0' + carry);
			a[f] = char(cur%10 + '0'), carry = cur/10;
			f--;
		}
		if (carry)
			a = "1" + a;
		return a;
	}
	string getNumber() {
		return number;
	}
	int toInt(string& s) {
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            res =  res * 10 + s[i] - '0';
        }
        return res;
    }
    string getSum (string num1, string num2) {
        int carry = 0;
        string res = "";
        if (num1.size() < num2.size()) 
            swap(num1, num2);
        int j = num1.size() - 1, cur = 0;
        for(int i = num2.size() - 1; i >= 0; --i) {
            cur = num1[j] - 2*'0' + num2[i] + carry;
            res += char(cur% 10 + '0');
            carry = cur/10;
            j--;
        }
        while (j >= 0) {
            cur = num1[j] - '0' + carry;
            res += char(cur%10 + '0');
            carry = cur/10;
            j--;
        }
        if (carry) {
            res += char(carry + '0');
        }
        reverse(res.begin(), res.end());
        if (res[0] == '0')
            return "0";
        return res;
    }
    string simpleMultiply(int c, string s) {
        int carry = 0, pos = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            int cur = s[i] - '0', sum = cur * c + carry;
            s[i] = char(sum%10+'0');
            carry = sum/10;
        }
        reverse(s.begin(), s.end());
        if (carry)
            s += char(carry + '0');
        reverse(s.begin(), s.end());
        return (s[0] == '0') ? "0" : s;
    }
	BigInt operator*(const BigInt& other) {
		string num1 = number, num2 = other.number;
		if (num1.size() < num2.size())
            swap(num1, num2);
        int n = num1.size(), m = num2.size();
        string sum = "0";
        string ans = "";
        for (int i = m - 1; i >= 0; --i) {
            sum = getSum(sum, simpleMultiply(num2[i] - '0', num1));
            ans += sum[sum.size() - 1];
            sum.pop_back();
        }
        while(!sum.empty()) {
            ans += sum[sum.size() - 1];
            sum.pop_back();
        }
        return reverse(ans.begin(), ans.end()), ans;
	}
};

BigInt dp[2222];
long long n, k;

int main() {

	cin >> n >> k;
	string kToStr = to_string(k - 1);
	dp[0] = {"1"}, dp[1] = {kToStr};
	BigInt K = {kToStr};

	for (int i = 2; i <= n; ++i) {
		dp[i] = (dp[i - 1] + dp[i - 2]) * K;
	}
    
	cout << dp[n].getNumber()<< endl;
}