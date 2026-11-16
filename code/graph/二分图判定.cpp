#include <cstddef>
#include <vector>

// adj 为 n 个顶点的无向图邻接表，编号从 1 开始。

vector<int> color(n + 1, -1), q;
bool bipartite = true;
for (int s = 1; s <= n && bipartite; ++s) {
    if (color[s] != -1) continue;
    color[s] = 0;
    q.assign(1, s);
    for (size_t i = 0; i < q.size() && bipartite; ++i) {
        int u = q[i];
        for (int v : adj[u]) {
            if (color[v] == color[u]) {
                bipartite = false;
                break;
            }
            if (color[v] != -1) continue;
            color[v] = color[u] ^ 1;
            q.push_back(v);
        }
    }
}
