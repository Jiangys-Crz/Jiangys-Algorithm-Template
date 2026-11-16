using ull = unsigned long long;

// In solve: ull n. Each block [l, r] has constant quotient q.

for (ull l = 1; l <= n; ) {
    ull q = n / l, r = n / q;
    // TODO: Accumulate the contribution of [l, r] with quotient q.
    if (r == n) break;
    l = r + 1;
}
