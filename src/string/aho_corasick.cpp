template <int ALPHA = 26, char FIRST = 'a'>
struct Aho {
    struct Node {
        array<int, ALPHA> mp, go;
        int fail = 0;
        bool end = false;
        Node() {
            mp.fill(-1);
            go.fill(-1);
        }
    };
    vector<Node> tree = {Node()};
    int charToIdx(char ch) const { return ch - FIRST; }
    void insert(const string &st) {
        int cur = 0;
        for (auto ch : st) {
            int i = charToIdx(ch);
            if (!~tree[cur].mp[i]) {
                tree[cur].mp[i] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].mp[i];
        }
        tree[cur].end = true;
    }
    void build() { // build O(ALPHA * sum(m_i))
        queue<int> q;
        for (int i = 0; i < ALPHA; i++) {
            int nxt = tree[0].mp[i];
            if (!~nxt) tree[0].go[i] = 0;
            else {
                tree[0].go[i] = nxt;
                q.push(nxt);
            }
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            tree[cur].end |= tree[tree[cur].fail].end;
            for (int i = 0; i < ALPHA; i++) {
                int nxt = tree[cur].mp[i];
                if (!~nxt) tree[cur].go[i] = tree[tree[cur].fail].go[i];
                else {
                    tree[cur].go[i] = nxt;
                    tree[nxt].fail = tree[tree[cur].fail].go[i];
                    q.push(nxt);
                }
            }
        }
    }
    bool findSubstring(const string &st) const { // O(N)
        int cur = 0;
        for (auto ch : st) {
            cur = tree[cur].go[charToIdx(ch)];
            if (tree[cur].end) return true;
        }
        return false;
    }
};