struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n + 1), rank(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int a) {
        return parent[a] == a ? a : parent[a] = find(parent[a]);
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rank[a] > rank[b]) swap(a, b);
        parent[a] = b;
        rank[b] += rank[a] == rank[b];
    }
    bool isConnected(int a, int b) {
        return find(a) == find(b);
    }
};