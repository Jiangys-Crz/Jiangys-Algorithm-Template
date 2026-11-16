using ull = unsigned long long;

// In solve: ull x. Negation on unsigned integers wraps modulo 2^64.
ull low = x & -x;
int count = 0;
for (ull y = x; y; y &= y - 1) ++count;
