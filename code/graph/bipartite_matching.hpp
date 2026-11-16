#include <algorithm>
#include <vector>

#ifndef XCPC_GRAPH_BIPARTITE_MATCHING_HPP
#define XCPC_GRAPH_BIPARTITE_MATCHING_HPP

struct BipartiteMatching {
    int n, m;
    vector<vector<int>> adj;
    vector<int> match, vis;

    BipartiteMatching(int n, int m)
        : n(n), m(m), adj(n + 1), match(m + 1), vis(m + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    int work() {
        fill(match.begin(), match.end(), 0);
        fill(vis.begin(), vis.end(), 0);
        int ans = 0;
        for (int u = 1; u <= n; ++u) ans += dfs(u, u);
        return ans;
    }

private:
    bool dfs(int u, int stamp) {
        for (int v : adj[u]) {
            if (vis[v] == stamp) continue;
            vis[v] = stamp;
            if (!match[v] || dfs(match[v], stamp)) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }
};

#endif
