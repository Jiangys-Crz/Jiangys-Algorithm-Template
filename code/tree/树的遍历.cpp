#include <cstddef>
#include <vector>

// 先准备 n 个节点的树的邻接表 adj 和根节点 root，编号从 1 开始。

vector<int> fa(n + 1), order, stk{root};
while (!stk.empty()) {
    int u = stk.back();
    stk.pop_back();
    order.push_back(u);
    // 待填写：若需要，在首次访问时处理节点 u。
    for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
        int v = *it;
        if (v == fa[u]) continue;
        fa[v] = u;
        stk.push_back(v);
    }
}
vector<int> dep(n + 1), q{root};
for (size_t i = 0; i < q.size(); ++i) {
    int u = q[i];
    for (int v : adj[u]) {
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        q.push_back(v);
    }
}
