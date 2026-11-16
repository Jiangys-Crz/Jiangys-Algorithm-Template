using ull = unsigned long long;

// elements 保存 [0, 63] 内的元素编号，b 为另一集合的掩码。
ull a = 0;
for (int x : elements) a |= 1ULL << x;
bool contains = (a & b) == b;
bool disjoint = (a & b) == 0;
