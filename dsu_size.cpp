// https://leetcode.com/problems/making-a-large-island/

class Solution {
public:
    class DSU {
        vector <int> parent, size;
    public: 
        DSU(int sz) : size(sz), parent(sz) {
            iota(parent.begin(), parent.end(), 0);
            fill(size.begin(), size.end(), 1);
        }
        int find_set(int a) {
            if (parent[a] == a)
                return a;
            parent[a] = find_set(parent[a]);
            return parent[a];
        }
        void union_set(int a, int b) {
            a = find_set(a), b = find_set(b);
            if (a != b) {
                if (size[a] < size[b])
                    swap(a, b);
                parent[b] = a;
                size[a] += size[b];
            }
        }
        int get_size(int a) {
            return size[find_set(a)];
        }
    };
    
    int largestIsland(vector<vector<int>>& grid) {
        const int R = grid.size(), C = grid[0].size();
        auto dsu = DSU(R*C + C);
        queue <pair <int, int>> q;
        const int DIR_X[4] = {0, 0, -1, 1}, DIR_Y[4] = {-1, 1, 0, 0}; 
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                int ind = i*C + j;
                if (grid[i][j] && dsu.find_set(ind) == ind) {
                    grid[i][j] = 2;
                    q.push({i, j});
                    while(!q.empty()) {
                        auto cur = q.front();
                        q.pop();
                        for (int k = 0; k < 4; ++k) {
                            int newR = cur.first + DIR_X[k], newC = cur.second + DIR_Y[k], newInd = newR*C + newC;
                            if (newR < 0 || newR >= R || newC < 0 || newC >= C) continue;
                            if (grid[newR][newC] == 1) {
                                grid[newR][newC] = 2;
                                dsu.union_set(newInd, ind);
                                q.push({newR, newC});
                            }
                        }
                    }
                }
            }
        }
        set <int> nei;
        int ans = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (!grid[i][j]) {
                    nei.clear();
                    for (int k = 0; k < 4; ++k) {
                        int newR = i + DIR_X[k], newC = j + DIR_Y[k], newInd = newR*C + newC;
                        if (newR < 0 || newR >= R || newC < 0 || newC >= C) continue;
                        if (grid[newR][newC] == 2) 
                            nei.insert(dsu.find_set(newInd));
                    }
                    int cur = 1;
                    for (int root : nei)
                        cur += dsu.get_size(root);
                    ans = max(ans, cur);
                } else {
                    ans = max(ans, dsu.get_size(i*C + j));
                }
            
            }
        }
        return ans;
    }
};