#include <algorithm>
#include <utility>
#include <vector>

#include "euclid.hpp"

std::optional<std::pair<int, ull>> nimMove(const std::vector<ull>& heaps) {
    ull x = 0;
    for (ull h : heaps) x ^= h;
    if (!x) return std::nullopt;
    for (int i = 0; i < static_cast<int>(heaps.size()); ++i) {
        ull after = heaps[i] ^ x;
        if (after < heaps[i]) return std::pair{i, after};
    }
    return std::nullopt;
}

std::vector<int> dagGrundy(const std::vector<std::vector<int>>& adj,
                           const std::vector<int>& order) {
    std::size_t maxDegree = 0;
    for (const auto& edges : adj) maxDegree = std::max(maxDegree, edges.size());
    std::vector<int> seen(maxDegree + 1, -1), sg(adj.size());
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int u = *it;
        for (int v : adj[u]) seen[sg[v]] = u;
        int x = 0;
        while (seen[x] == u) ++x;
        sg[u] = x;
    }
    return sg;
}
