#include <array>
#include <limits>
#include <vector>

long double expectedSteps(const std::vector<std::array<long double, 2>>& moves) {
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
    return next;
}
