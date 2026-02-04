template <typename T>
struct Trie {
    struct Node {
        map<T, Node *> mp;
        bool end = false;
        ~Node() { for (auto &[_, node] : mp) delete node; }
        Node *go(T val) {
            if (!mp.count(val)) mp[val] = new Node;
            return mp[val];
        }
    } *root;
    Trie() : root(new Node()) {}
    ~Trie() { delete root; }
    void insert(const vector<T> &v) { // O(N)
        Node *cur = root;
        for (auto &e : v) cur = cur->go(e);
        cur->end = true;
    }
    bool find(const vector<T> &v) { // O(N)
        Node *cur = root;
        for (auto &e : v) {
            if (!cur->mp.count(e)) return false;
            cur = cur->go(e);
        }
        return cur->end;
    }
};