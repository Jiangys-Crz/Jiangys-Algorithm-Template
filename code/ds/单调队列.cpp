using ll = long long;

// 先准备长度为 n 的数组 a，窗口宽度满足 1 <= k <= n。
// ans 按顺序保存各完整窗口的最小值。

deque<int> q;
vector<ll> ans;
for (int i = 0; i < n; ++i) {
    while (!q.empty() && q.front() <= i - k) q.pop_front();
    while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
    q.push_back(i);
    if (i + 1 >= k) ans.push_back(a[q.front()]);
}
