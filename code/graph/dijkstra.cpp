std::vector<ll> dijkstra(int n, std::vector<std::vector<pair<int, int>>> &g, int s) {
    std::vector<ll> dist(n + 1, inf);
    std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, greater<>> pq;

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