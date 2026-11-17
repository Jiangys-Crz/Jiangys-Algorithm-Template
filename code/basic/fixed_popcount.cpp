using ull = unsigned long long;

// 0 <= k <= n < 64。空子集单独处理。
if (k == 0) {
    // 待填写：处理空子集。
} else {
    ull limit = 1ULL << n;
    for (ull mask = (1ULL << k) - 1; mask < limit; ) {
        // 待填写：处理当前含 k 个元素的子集 mask。
        ull low = mask & -mask;
        ull next = mask + low;
        if (next >= limit) break;
        mask = next | (((next ^ mask) >> 2) / low);
    }
}
