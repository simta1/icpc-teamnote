int dfsi = 0;
void ett(int cur, int par) {
    in[cur] = ++dfsi;
    for (int next : adj[cur]) if (next != par) ett(next, cur);
    out[cur] = dfsi;
}
// root->v path add update / v point query
// update(in[v], 1) / query(in[v], out[v])