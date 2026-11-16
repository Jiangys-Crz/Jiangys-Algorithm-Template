#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using ll = long long;

// In solve: 1-based adj[u] of (v, w), w >= 0, int n and sources.
// dist[u] is the minimum distance from any source; inf means unreachable.

constexpr ll inf = std::numeric_limits<ll>::max() / 4;
std::vector<ll> dist(n + 1, inf);

using State = std::pair<ll, int>;
std::priority_queue<State, std::vector<State>, std::greater<>> pq;
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
