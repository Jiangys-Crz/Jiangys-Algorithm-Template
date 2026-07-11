std::vector<i64> dijkstra(int n, std::vector<std::vector<pair<int, int>>> &g, int s) {
    std::vector<i64> dist(n + 1, inf);
    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, greater<>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}