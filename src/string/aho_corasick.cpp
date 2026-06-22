template <int ALPHA = 26, char FIRST = 'a'>
struct AhoCorasick {
    struct Node {
        array<int, ALPHA> mp, go;
        int fail = 0;
        bool end = false;
        Node() {
            mp.fill(-1);
            go.fill(-1);
        }
    };
    vector<Node> tr = {Node()};
    int charToIdx(char ch) const { return ch - FIRST; }
    void insert(const string &st) {
        int cur = 0;
        for (auto ch : st) {
            int i = charToIdx(ch);
            if (!~tr[cur].mp[i]) {
                tr[cur].mp[i] = tr.size();
                tr.emplace_back();
            }
            cur = tr[cur].mp[i];
        }
        tr[cur].end = true;
    }
    void build() { // build O(ALPHA * sum(m_i))
        queue<int> q;
        for (int i = 0; i < ALPHA; i++) {
            int next = tr[0].mp[i];
            if (!~next) tr[0].go[i] = 0;
            else {
                tr[0].go[i] = next;
                q.push(next);
            }
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            tr[cur].end |= tr[tr[cur].fail].end;
            for (int i = 0; i < ALPHA; i++) {
                int next = tr[cur].mp[i];
                if (!~next) tr[cur].go[i] = tr[tr[cur].fail].go[i];
                else {
                    tr[cur].go[i] = next;
                    tr[next].fail = tr[tr[cur].fail].go[i];
                    q.push(next);
                }
            }
        }
    }
    bool findSubstring(const string &st) const { // O(N)
        int cur = 0;
        for (auto ch : st) {
            cur = tr[cur].go[charToIdx(ch)];
            if (tr[cur].end) return true;
        }
        return false;
    }
};