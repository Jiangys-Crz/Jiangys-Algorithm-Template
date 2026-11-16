#include <vector>

// In solve: undirected 1-based graph adj with n vertices.
// cnt is the component count; bel[u] is the component of u.

std::vector<int> bel(n + 1), stk;
int cnt = 0;
for (int s = 1; s <= n; ++s) {
    if (bel[s]) continue;
    bel[s] = ++cnt;
    stk.push_back(s);
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        for (int v : adj[u]) {
            if (bel[v]) continue;
            bel[v] = cnt;
            stk.push_back(v);
        }
    }
}
