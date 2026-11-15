#include <cstdint>
#include <vector>

// Element IDs must be in [0, 63]. Duplicates represent the same element.
std::uint64_t makeMask(const std::vector<int>& elements) {
    std::uint64_t mask = 0;
    for (int element : elements) {
        mask |= std::uint64_t{1} << element;
    }
    return mask;
}

bool containsAll(std::uint64_t mask, std::uint64_t required) {
    return (mask & required) == required;
}

bool isDisjoint(std::uint64_t first, std::uint64_t second) {
    return (first & second) == 0;
}
