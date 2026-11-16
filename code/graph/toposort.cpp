// 先准备 n 个顶点的有向图邻接表 adj，顶点编号从 1 开始。

vector<int> deg(n + 1), order;
for (int u = 1; u <= n; ++u) {
    for (int v : adj[u]) ++deg[v];
}
for (int u = 1; u <= n; ++u) {
    if (!deg[u]) order.push_back(u);
}
for (size_t i = 0; i < order.size(); ++i) {
    for (int v : adj[order[i]]) {
        if (--deg[v] == 0) order.push_back(v);
    }
}
bool acyclic = order.size() == static_cast<size_t>(n);
