#include <cstdint>

std::uint64_t lowbit(std::uint64_t mask) {
    return mask & (std::uint64_t{0} - mask);
}

int countSetBits(std::uint64_t mask) {
    int count = 0;
    while (mask != 0) {
        mask -= lowbit(mask);
        ++count;
    }
    return count;
}
