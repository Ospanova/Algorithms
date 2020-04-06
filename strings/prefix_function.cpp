
// 214. Shortest Palindrome

class Solution {
public:
    vector <int> pr_function(string& s) {
	    int n = s.size();
	    vector <int> pr(n, 0);
        for (int i = 1, j; i < n; ++i) {
            j = pr[i - 1];
            while (j > 0 && s[i] != s[j])
                j = pr[j - 1];
            if (s[i] == s[j]) j++;
            pr[i] = j;
        }
        return pr;
    }
    
    string shortestPalindrome(string s) {
        string reversed = s;
        reverse(reversed.begin(), reversed.end());
        string new_s = s + "#" + reversed; // for finding common of prefix s and suffix of reversed
        int n = new_s.size(), m = s.size();
        auto pr = pr_function(new_s);
        return reversed.substr(0, m - pr[n - 1]) + s;
    }
};
