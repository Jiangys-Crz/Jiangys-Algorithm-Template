#include <algorithm>
#include <cstddef>
#include <vector>

using ull = unsigned long long;

// In solve: heaps contains the Nim heap sizes.
ull x = 0;
for (ull h : heaps) x ^= h;
int heap = -1;
ull after = 0;
if (x) {
    for (int i = 0; i < static_cast<int>(heaps.size()); ++i) {
        if ((heaps[i] ^ x) < heaps[i]) {
            heap = i;
            after = heaps[i] ^ x;
            break;
        }
    }
}

// For DAG games: adj is 0-based, order is a topological order.
std::size_t maxDegree = 0;
for (const auto& edges : adj) maxDegree = std::max(maxDegree, edges.size());
std::vector<int> seen(maxDegree + 1, -1), sg(adj.size());
for (auto it = order.rbegin(); it != order.rend(); ++it) {
    int u = *it;
    for (int v : adj[u]) seen[sg[v]] = u;
    int mex = 0;
    while (seen[mex] == u) ++mex;
    sg[u] = mex;
}
