namespace Poly { // multipoint evaluation
    template <ll p, ll primitiveRoot, typename T>
    vector<ll> multiEval(const vector<T> &f, const vector<T> &qs) { // O(NlogN + qlog^2q)
        if (qs.empty()) return {};
        assert(!f.empty());
        vector<vector<ll> > tree(4 * qs.size());
        auto build = [&](auto &&build, int node, int s, int e) {
            if (s == e) {
                tree[node] = {(p - qs[s] % p) % p, 1};
                return;
            }
            int m = s + e >> 1;
            build(build, node << 1, s, m);
            build(build, node << 1 | 1, m + 1, e);
            tree[node] = multiplyMod<p, primitiveRoot>(tree[node << 1], tree[node << 1 | 1]);
        };
        build(build, 1, 0, qs.size() - 1); // O(qlog^2q)
        vector<ll> res(qs.size());
        auto eval = [&](auto &&eval, vector<ll> poly, int node, int s, int e) {
            poly = remainderMod<p, primitiveRoot>(poly, tree[node]);
            if (s == e) {
                assert(!poly.empty());
                res[s] = poly[0];
                return;
            }
            int m = s + e >> 1;
            eval(eval, poly, node << 1, s, m);
            eval(eval, poly, node << 1 | 1, m + 1, e);
        };
        eval(eval, f, 1, 0, qs.size() - 1);
        return res;
    }
}
