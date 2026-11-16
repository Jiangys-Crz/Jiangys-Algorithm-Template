using ll = long long;

// a 保存若干非递减序列。

using State = tuple<ll, size_t, size_t>;
priority_queue<State, vector<State>, greater<>> pq;
for (size_t i = 0; i < a.size(); ++i) {
    if (!a[i].empty()) pq.push({a[i][0], i, 0});
}

while (!pq.empty()) {
    auto [x, i, j] = pq.top();
    pq.pop();
    // 待填写：按合并后的顺序处理当前元素 x。
    if (j + 1 < a[i].size()) pq.push({a[i][j + 1], i, j + 1});
}
