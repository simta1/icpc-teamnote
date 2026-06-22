vector<array<int, 26> > getAutomaton(const string &st) { // O(26N)
    int n = st.size();
    vector<array<int, 26> > go(n + 1);
    auto pi = getPi(st);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (i < n && st[i] == j + 'a') go[i][j] = i + 1;
            else go[i][j] = i ? go[pi[i - 1]][j] : 0;
        }
    }
    return go;
}
