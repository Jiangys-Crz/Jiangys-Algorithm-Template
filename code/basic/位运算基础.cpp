using ull = unsigned long long;

// mask 为 64 位无符号掩码，位编号 bit 满足 0 <= bit < 64。
ull flag = 1ULL << bit;
bool test = (mask & flag) != 0;
ull set = mask | flag;
ull clear = mask & ~flag;
ull toggle = mask ^ flag;
