#include <iostream>
#include <vector>

using ull = unsigned long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    if (n < 2) {
        std::cout << "NONE\n";
        return 0;
    }
    std::vector<ull> values(n);
    for (ull& x : values) std::cin >> x;

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
    std::cout << answer << '\n';
}
