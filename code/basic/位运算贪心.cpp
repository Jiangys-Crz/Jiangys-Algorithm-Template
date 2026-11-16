#include <vector>

using ull = unsigned long long;

// In solve: vector<ull> values with at least two elements.

ull answer = 0;
for (int bit = 63; bit >= 0; --bit) {
    ull candidate = answer | (1ULL << bit);
    int matches = 0;
    for (ull value : values) {
        if ((value & candidate) == candidate && ++matches == 2) {
            answer = candidate;
            break;
        }
    }
}
