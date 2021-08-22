vector <vector<int>> getManaher(string& s) {
      vector <int> maxLen(s.size());

      int L = 0, R = -1;

      for (int i = 0; i < s.size(); ++i) {
          if (i <= R) 
              maxLen[i] = min(R - i + 1, maxLen[L + (R - i)]);
          int r = i + maxLen[i], l = i - maxLen[i];
          while (r < s.size() && l >= 0 && s[l] == s[r]) {
              r++, l--;
              maxLen[i]++;
          }
          l++, r--;
          if (r > R) 
              L = l, R = r;
      }


      vector <int> maxLenEven(s.size());

      L = 0, R = -1;
      for (int i = 0; i < s.size(); ++i) {
          if (i <= R) 
              maxLenEven[i] = min(R - i + 1, maxLenEven[L + (R - i) + 1]);
          int r = i + maxLenEven[i], l = i - maxLenEven[i] - 1;
          while (r < s.size() && l >= 0 && s[l] == s[r]) {
              r++, l--;
              maxLenEven[i]++;
          }
          l++, r--;
          if (r > R) 
              L = l, R = r;
      }


      return {maxLen, maxLenEven};
  }
