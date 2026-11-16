using ull = unsigned long long;

// In solve: elements contains indices in [0, 63]; ull b is another mask.
ull a = 0;
for (int x : elements) a |= 1ULL << x;
bool contains = (a & b) == b;
bool disjoint = (a & b) == 0;
