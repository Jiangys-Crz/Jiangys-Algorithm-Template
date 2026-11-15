#include <cstdint>
#include <optional>
#include <vector>

std::optional<std::uint64_t> maxPairAnd(const std::vector<std::uint64_t>& values) {
    if (values.size() < 2) {
        return std::nullopt;
    }

    std::uint64_t answer = 0;
    for (int bit = 63; bit >= 0; --bit) {
        const std::uint64_t candidate = answer | (std::uint64_t{1} << bit);
        int matches = 0;
        for (std::uint64_t value : values) {
            if ((value & candidate) == candidate && ++matches == 2) {
                answer = candidate;
                break;
            }
        }
    }
    return answer;
}
