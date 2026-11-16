#include <vector>

// 先准备邻接表 graph 和有效起点 start，编号从 0 开始。

vector<char> visited(graph.size(), false);
vector<int> order;
auto dfs = [&](auto&& self, int v) -> void {
    visited[v] = true;
    order.push_back(v);
    // 待填写：若需要，在进入顶点 v 时处理它。
    for (int u : graph[v]) {
        if (!visited[u]) {
            self(self, u);
        }
    }
};
dfs(dfs, start);
