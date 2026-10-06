struct Sqdc {
    vector<int> val, sum;
    static constexpr int B =  447;
    Sqdc(int n) : val(n), sum((n + B - 1) / B) {}
    void upd(int i, int add) {
        val[i] += add;
        sum[i / B] += add;
    }
    int qry(int l, int r) { // O(B + n / B)
        int res = 0;
        while (l <= r && l % B) res += val[l++];
        while (l + B - 1 <= r) {
            res += sum[l / B];
            l += B;
        }
        while (l <= r) res += val[l++];
        return res;
    }
};
