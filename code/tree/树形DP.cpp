using ll = long long;

// 先预处理树 tr，并按题目定义动态规划状态。
vector<array<ll, 2>> dp(tr.n + 1);
for (int u = 1; u <= tr.n; ++u) {
    dp[u] = /* 待填写：合并子树前节点 u 的初始状态 */;
}

for (int i = tr.n; i >= 2; --i) {
    int u = tr.id[i], p = tr.fa[u];
    // 待填写：将子节点 u 的已知状态合并到父节点 p。
}
ll ans = /* 待填写：从根节点状态 dp[tr.root] 提取答案 */;
