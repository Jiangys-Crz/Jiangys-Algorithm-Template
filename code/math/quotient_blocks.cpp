using ull = unsigned long long;

// n 为无符号整数。每个区间 [l, r] 内的整除商均为 q。

for (ull l = 1; l <= n; ) {
    ull q = n / l, r = n / q;
    // 待填写：按整除商 q 累加区间 [l, r] 的贡献。
    if (r == n) break;
    l = r + 1;
}
