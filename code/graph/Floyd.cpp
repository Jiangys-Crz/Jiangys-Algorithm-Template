using ll = long long;
using lll = __int128;

// 先准备 n 个顶点及有向边 (u, v, w)，编号从 1 开始。
// 无向边按两个方向各存一次。

constexpr lll inf = lll{1} << 100;
vector<vector<lll>> dist(n + 1, vector<lll>(n + 1, inf));
for (int u = 1; u <= n; ++u) dist[u][u] = 0;
for (auto [u, v, w] : edges) {
    dist[u][v] = min(dist[u][v], lll(w));
}
for (int k = 1; k <= n; ++k) {
    for (int u = 1; u <= n; ++u) {
        if (dist[u][k] == inf) continue;
        for (int v = 1; v <= n; ++v) {
            if (dist[k][v] == inf) continue;
            lll nd = max(-inf, dist[u][k] + dist[k][v]);
            dist[u][v] = min(dist[u][v], nd);
        }
    }
}
