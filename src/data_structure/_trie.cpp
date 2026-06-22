template <typename T>
struct Trie {
    struct Node {
        map<T, int> mp;
        bool end = false;
    };
    vector<Node> tr = {Node()};
    void insert(const vector<T> &v) { // O(N)
        int cur = 0;
        for (auto &e : v) {
            if (!tr[cur].mp.count(e)) {
                tr[cur].mp[e] = tr.size();
                tr.emplace_back();
            }
            cur = tr[cur].mp[e];
        }
        tr[cur].end = true;
    }
    bool find(const vector<T> &v) { // O(N)
        int cur = 0;
        for (auto &e : v) {
            if (!tr[cur].mp.count(e)) return false;
            cur = tr[cur].mp[e];
        }
        return tr[cur].end;
    }
};