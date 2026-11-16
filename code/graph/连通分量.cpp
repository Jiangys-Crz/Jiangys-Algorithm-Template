// adj 为 n 个顶点的无向图邻接表，编号从 1 开始。
// cnt 为连通分量数，bel[u] 为 u 所属的分量编号。

vector<int> bel(n + 1), stk;
int cnt = 0;
for (int s = 1; s <= n; ++s) {
    if (bel[s]) continue;
    bel[s] = ++cnt;
    stk.push_back(s);
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        for (int v : adj[u]) {
            if (bel[v]) continue;
            bel[v] = cnt;
            stk.push_back(v);
        }
    }
}
