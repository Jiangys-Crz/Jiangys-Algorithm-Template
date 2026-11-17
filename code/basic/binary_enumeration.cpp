using ull = unsigned long long;

// n 为元素个数，满足 0 <= n < 64。
for (ull mask = 0; mask < (1ULL << n); ++mask) {
    for (ull s = mask; s; s &= s - 1) {
        int i = __builtin_ctzll(s);
        // 待填写：处理当前子集中的元素 i。
    }
    // 待填写：处理完整子集 mask，包含空子集。
}
