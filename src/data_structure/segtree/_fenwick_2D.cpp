struct BIT {
    vector<ordered_set<int>> tree;
    BIT(int n) : tree(n + 1) {}
    void insert(int x, int y) {
        for (; x < tree.size(); x += x & -x) tree[x].insert(y);
    }
    void erase(int x, int y) {
        for (; x < tree.size(); x += x & -x) tree[x].erase(y);
    }
    int sum(int x, int y) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += tree[x].order_of_key(y + 1);
        return res;
    }
    int query(int x1, int x2, int y1, int y2) {
        return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1 ,y2) + sum(x1 - 1, y1 - 1);
    }
};

struct BIT {
    vector<vector<int>> tree, ys;
    BIT(int n) : tree(n + 1), ys(n + 1) {}
    void add(int x, int y) {
        for (; x < tree.size(); x += x & -x) ys[x].push_back(y);
    }
    void compress() {
        for (auto &v : ys) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        }
        for (int x = 0; x < tree.size(); x++) {
             tree[x].resize(ys[x].size() + 1);
        }
    }
    void insert(int x, int y) {
        for (; x < tree.size(); x += x & -x) {
            int idx = lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin() + 1;
            for (int i = idx; i < tree[x].size(); i += i & -i) ++tree[x][i];
        }
    }
    void erase(int x, int y) {
        for (; x < tree.size(); x += x & -x) {
            int idx = lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin() + 1;
            for (int i = idx; i < tree[x].size(); i += i & -i) --tree[x][i];
        }
    }
    int sum(int x, int y) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            int idx = upper_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin() - 1 + 1;
            for (int i = idx; i > 0; i -= i & -i) res += tree[x][i];
        }
        return res;
    }
    int query(int x1, int x2, int y1, int y2) {
        return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1 ,y2) + sum(x1 - 1, y1 - 1);
    }
};
