using ull = unsigned long long;

// x 为 64 位无符号整数，取负按 2^64 取模。
ull low = x & -x;
int count = 0;
for (ull y = x; y; y &= y - 1) ++count;
