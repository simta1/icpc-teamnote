struct Node {
    Node *chd[2];
};

Node *root = new Node();
auto insert = [&](int x) {
    Node *cur = root;
    for (int i = 29; i >= 0; i--) {
        int bit = x >> i & 1;
        if (!cur->chd[bit]) cur->chd[bit] = new Node();
        cur = cur->chd[bit];
    }
};

auto mnquery = [&](int x) {
    Node *cur = root;
    for (int i = 29; i >= 0; i--) {
        int bit = x >> i & 1;
        if (!cur->chd[bit]) bit ^= 1;
        cur = cur->chd[bit];
        x ^= bit << i;
    }
    return x;
};

int f(int x, int k) { // min_{s in {0,1,...,k}} {s ^ x}
    int have = k;
    for(int i = 29; i >= 0; i--) if (x >> i & 1) {
        if (have >= (1 << i)) {
            have -= (1 << i);
            x ^= (1 << i);
        }
    }
    return x;
}