struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        while (p[a] != a) a = p[a] = p[p[a]];
        return a;
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (r[a] > r[b]) swap(a, b);
        p[a] = b;
        r[b] += r[a] == r[b];
    }
};