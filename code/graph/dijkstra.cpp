using ll = long long;

// 邻接表 adj[u] 保存 (v, w)，边权非负。n 为顶点数，sources 为源点集合，编号从 1 开始。
// dist[u] 为各源点到 u 的最短距离的最小值，inf 表示不可达。

constexpr ll inf = numeric_limits<ll>::max() / 4;
vector<ll> dist(n + 1, inf);

using State = pair<ll, int>;
priority_queue<State, vector<State>, greater<>> pq;
for (int s : sources) {
    if (dist[s] == 0) continue;
    dist[s] = 0;
    pq.push({0, s});
}
while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d != dist[u]) continue;
    for (auto [v, w] : adj[u]) {
        if (w >= inf - d) continue;
        ll nd = d + w;
        if (nd >= dist[v]) continue;
        dist[v] = nd;
        pq.push({nd, v});
    }
}
