using ull = unsigned long long;

// In solve: ull mask; int bit with 0 <= bit < 64.
ull flag = 1ULL << bit;
bool test = (mask & flag) != 0;
ull set = mask | flag;
ull clear = mask & ~flag;
ull toggle = mask ^ flag;
