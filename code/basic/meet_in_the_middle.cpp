using ull = unsigned long long;

// initial 是空子集状态，take(old, i) 在旧状态后追加第 i 项。
// 下标从 0 开始，每半的元素数须小于 ull 的位宽。
auto enumerate = [&](int l, int r) {
    ull limit = 1ULL << (r - l);
    vector<State> states{initial};
    states.reserve(limit);
    constexpr int width = numeric_limits<ull>::digits;
    for (ull mask = 1; mask < limit; ++mask) {
        int bit = width - 1 - __builtin_clzll(mask);
        ull prev = mask ^ (1ULL << bit);
        states.push_back(take(states[prev], l + bit));
    }
    return states;
};

int mid = n / 2;
auto left = enumerate(0, mid);
auto right = enumerate(mid, n);

// 待填写：根据两侧关系，为 right 排序或建立哈希表。
for (const auto& x : left) {
    // 待填写：按 x 查询符合条件的右侧状态，并更新答案。
}
