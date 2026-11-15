#include <cstdint>

// Each function requires 0 <= bit < 64.
bool testBit(std::uint64_t mask, int bit) {
    return (mask & (std::uint64_t{1} << bit)) != 0;
}

std::uint64_t setBit(std::uint64_t mask, int bit) {
    return mask | (std::uint64_t{1} << bit);
}

std::uint64_t clearBit(std::uint64_t mask, int bit) {
    return mask & ~(std::uint64_t{1} << bit);
}

std::uint64_t toggleBit(std::uint64_t mask, int bit) {
    return mask ^ (std::uint64_t{1} << bit);
}
