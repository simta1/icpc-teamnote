struct DSU {
    vector<int> p, sz;
    int n;
    DSU(int n) : p(2 * n), sz(2 * n), n(n) {
        iota(p.begin(), p.end(), 0);
        fill(sz.begin(), sz.begin() + n, 1);
    }
    int find(int a) {
        return p[a] == a ? a : p[a] = find(p[a]);
    }
    void _merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        p[a] = b;
        sz[b] += sz[a];
    }
    void merge(int a, int b, bool isOpp) {
        if (isOpp) {
            _merge(a, b + n);
            _merge(a + n, b);
        }
        else {
            _merge(a, b);
            _merge(a + n, b + n);
        }
    }
    int query(int a, int b) { // 0: 같은 집합, 1: 반대쪽 집합, -1: 관계 모름
        return find(a) == find(b) ? 0 : find(a) == find(b + n) ? 1 : -1;
    }
};
