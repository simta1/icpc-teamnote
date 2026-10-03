using ull = unsigned long long;
using mat = vector<vector<ull>>;
mat mul(const mat &a, const mat &b, ull mod) {
    int n = a.size(), m = b.size(), p = b[0].size();

    mat bt(p, vector<ull>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            bt[j][i] = b[i][j];
        }
    }

    mat res(n, vector<ull>(p));
    constexpr int B = 16;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < p; k++) {
            ull sum = 0;
            for (int j1 = 0; j1 < m; j1 += B) {
                int j2 = min(m, j1 + B);
                for (int j = j1; j < j2; j++) sum += a[i][j] * bt[k][j];
                sum %= mod;
            }
            res[i][k] = sum;
        }
    }
    return res;
}
