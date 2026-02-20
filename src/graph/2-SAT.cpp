struct TwoSat {
    int n;
    vector<vector<int> > adj;
    vector<int> sccn;
    TwoSat(int n) : n(n), adj(2 * n) {}
    int f(int a) {
        if (a > 0) return 2 * (a - 1);
        return 2 * (-a - 1) + 1;
    }
    // 전부 1-based
    void add2SAT(int a, int b) { // a or b가 true
        adj[f(-a)].push_back(f(b));
        adj[f(-b)].push_back(f(a));
    }
    void add1SAT(int a) { adj[f(-a)].push_back(f(a)); } // a가 true
    void addEqual2SAT(int a, int b) { add2SAT(a, -b); add2SAT(-a, b); } // a == b 가 true
    void addNotEqual2SAT(int a, int b) { add2SAT(a, b); add2SAT(-a, -b); } // a != b 가 true // a, b 중 정확히 하나만 true
    void add22SAT(int a1, int a2, int b1, int b2) { add2SAT(a1, b1); add2SAT(a1, b2); add2SAT(a2, b1); add2SAT(a2, b2); } // (a1 and a2) or (b1 and b2)가 true
    void addNMSAT(const vector<int> &as, const vector<int> &bs) { for (auto &a : as) for (auto &b : bs) add2SAT(a, b); } // (a1 and a2 and ... and aN) or (b1 and b2 and ... and bM)가 true
    void addAtLeastTwo(int a, int b, int c) { add2SAT(a, b); add2SAT(b, c); add2SAT(c, a); } // a, b, c 중 2개 이상이 true
    void addAtMostOne(const vector<int> &v) { // v[0], v[1], ..., v[n - 1] 중 최대 하나만 true
        if (v.size() <= 1) return;
        adj.resize(2 * (n + v.size()));
        for (int i = 0; i < v.size(); i++) add2SAT(-v[i], n + 1 + i);
        for (int i = 1; i < v.size(); i++) {
            int cur = n + 1 + i;
            int prv = n + i;
            add2SAT(-prv, cur);
            add2SAT(-prv, -v[i]);
        }
        n += v.size();
    }
    void findSCC() {
        sccn.assign(2 * n, -1); // addAtMostOne호출하면 n 증가하기 때문에 findSCC()할 때마다 2*n+1로 설정해줘야 함
        vector<int> dfsn(2 * n, 0);
        vector<int> s(2 * n);
        int top = 0, dfsi = 0, scci = 0;
        function<int(int)> dfs = [&](int cur) -> int {
            int low = dfsn[cur] = ++dfsi;
            s[top++] = cur;
            for (auto next : adj[cur]) if (!~sccn[next]) low = min(low, dfsn[next] ? dfsn[next] : dfs(next));
            if (low == dfsn[cur]) {
                do { sccn[s[--top]] = scci; } while (s[top] != cur);
                ++scci;
            }
            return low;
        };
        for (int i = 0; i < 2 * n; i++) if (!dfsn[i]) dfs(i);
    }
    bool solve() { // O(V + E) // V는 변수개수, E는 절 개수
        findSCC();
        for (int i = 1; i <= n; i++) if (sccn[f(i)] == sccn[f(-i)]) return false;
        return true;
    }
    bool getSolution(int i) { // 1-based
        return sccn[f(-i)] > sccn[f(i)]; // sccn뒤집어져있어서
    }
};
// false/true는 -/+로 표현   
// graph.add2SAT(-1, 2); // (!x1 or x2) 
// graph.add2SAT(-2, -3); // (!x2 or !x3)