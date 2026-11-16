using ll = long long;

// 邻接表 adj[u] 保存 (v, w)，边权为 0 或 1。n 为顶点数，s 为起点，编号从 1 开始。
// dist[u] 为到 u 的最短距离，inf 表示不可达。

constexpr ll inf = numeric_limits<ll>::max() / 4;
vector<ll> dist(n + 1, inf);

deque<pair<ll, int>> q{{0, s}};
dist[s] = 0;
while (!q.empty()) {
    auto [d, u] = q.front();
    q.pop_front();
    if (d != dist[u]) continue;
    for (auto [v, w] : adj[u]) {
        ll nd = d + w;
        if (nd >= dist[v]) continue;
        dist[v] = nd;
        if (w == 0) q.push_front({nd, v});
        else q.push_back({nd, v});
    }
}
