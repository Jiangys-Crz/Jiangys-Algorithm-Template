#include <queue>
#include <vector>

// 先准备无权图邻接表 graph 和有效起点 start，编号从 0 开始。

vector<int> dist(graph.size(), -1);
queue<int> q;
dist[start] = 0;
q.push(start);
while (!q.empty()) {
    int v = q.front();
    q.pop();
    // 待填写：处理顶点 v，或在发现邻点时记录其前驱。
    for (int u : graph[v]) {
        if (dist[u] == -1) {
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }
}
