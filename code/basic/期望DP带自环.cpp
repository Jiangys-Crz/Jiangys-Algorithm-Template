#include <iomanip>
#include <iostream>
#include <array>
#include <limits>
#include <vector>

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<std::array<long double, 2>> moves(n);
    for (auto& [p1, p2] : moves) std::cin >> p1 >> p2;

    long double next = 0, nextTwo = 0;
    for (auto it = moves.rbegin(); it != moves.rend(); ++it) {
        const auto [p1, p2] = *it;
        const long double advance = p1 + p2;
        if (advance == 0) {
            nextTwo = next;
            next = std::numeric_limits<long double>::infinity();
            continue;
        }

        long double weighted = 1;
        if (p1 > 0) weighted += p1 * next;
        if (p2 > 0) weighted += p2 * nextTwo;
        nextTwo = next;
        next = weighted / advance;
    }
    std::cout << std::setprecision(15) << next << '\n';
}
