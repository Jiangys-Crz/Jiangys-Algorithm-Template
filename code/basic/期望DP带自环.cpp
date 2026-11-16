#include <array>
#include <limits>
#include <vector>

// In solve: moves[i] is the pair of step-1 and step-2 probabilities.
// Each pair is nonnegative and sums to at most 1.

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
long double ans = next;
