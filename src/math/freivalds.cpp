template <typename T>
bool freivalds(const vector<vector<T> > &a, const vector<vector<T> > &b, const vector<vector<T> > &c) { // O(K N^2)
    int n = a.size();
    vector<unsigned long long> Bx(n), x(n);
    static Random<int> rand(0, 1);
    constexpr int K = 30;
    for (int it = K; it--;) {
        for (auto &e : x) e = rand();
        for (int i = 0; i < n; i++) {
            Bx[i] = 0;
            for (int j = 0; j < n; j++) Bx[i] += b[i][j] * x[j];
        }
        for (int i = 0; i < n; i++) {
            unsigned long long ABx_i = 0, Cx_i = 0;
            for (int j = 0; j < n; j++) {
                ABx_i += a[i][j] * Bx[j];
                Cx_i += c[i][j] * x[j];
            }
            if (ABx_i != Cx_i) return false;
        }
    }
    return true;
}
// n*n행렬 A, B, C에 대해 AB==C(mod 2^64)확인 