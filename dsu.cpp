class DSU {
public:
    DSU(int sz) : sz_(sz) , parent_(sz) {
        iota(parent_.begin(), parent_.end(), 0);
    }
    int findSet(int a) {
        if (a != parent_[a])  
            parent_[a] = findSet(parent_[a]);
        return parent_[a];
    } 
    void unionSet(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (b != a) 
            parent_[min(a, b)] = max(a, b), sz_--;
    }
    
    int getSize() {
        return sz_;
    }
private:
    vector <int> parent_;
    int sz_;
};
