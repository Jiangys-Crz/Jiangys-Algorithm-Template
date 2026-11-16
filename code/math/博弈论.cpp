using ull = unsigned long long;

// heaps 存放各石子堆的大小。
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

// 有向无环图上的博弈使用邻接表 adj 和拓扑序 order，编号从 0 开始。
size_t maxDegree = 0;
for (const auto& edges : adj) maxDegree = max(maxDegree, edges.size());
vector<int> seen(maxDegree + 1, -1), sg(adj.size());
for (auto it = order.rbegin(); it != order.rend(); ++it) {
    int u = *it;
    for (int v : adj[u]) seen[sg[v]] = u;
    int mex = 0;
    while (seen[mex] == u) ++mex;
    sg[u] = mex;
}
