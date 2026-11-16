#include <deque>
#include <limits>
#include <utility>
#include <vector>

using ll = long long;

// In solve: 1-based adj[u] of (v, w), w in {0, 1}, int n and source s.
// dist[u] is the shortest distance; inf means unreachable.

constexpr ll inf = std::numeric_limits<ll>::max() / 4;
std::vector<ll> dist(n + 1, inf);

std::deque<std::pair<ll, int>> q{{0, s}};
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
