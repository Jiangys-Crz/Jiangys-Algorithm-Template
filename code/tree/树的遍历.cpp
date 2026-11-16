#include <cstddef>
#include <vector>

// In solve: 1-based tree adj with n vertices and root.

std::vector<int> fa(n + 1), order, stk{root};
while (!stk.empty()) {
    int u = stk.back();
    stk.pop_back();
    order.push_back(u);
    // TODO: Process u in preorder if needed.
    for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
        int v = *it;
        if (v == fa[u]) continue;
        fa[v] = u;
        stk.push_back(v);
    }
}
std::vector<int> dep(n + 1), q{root};
for (std::size_t i = 0; i < q.size(); ++i) {
    int u = q[i];
    for (int v : adj[u]) {
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        q.push_back(v);
    }
}
