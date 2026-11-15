#include <cstddef>
#include <cstdint>
#include <vector>

class PrefixXor {
public:
    explicit PrefixXor(const std::vector<std::uint64_t>& values)
        : prefix_(values.size() + 1, 0) {
        for (std::size_t i = 0; i < values.size(); ++i) {
            prefix_[i + 1] = prefix_[i] ^ values[i];
        }
    }

    // Returns the XOR of the 0-based half-open range [left, right).
    std::uint64_t query(std::size_t left, std::size_t right) const {
        return prefix_[right] ^ prefix_[left];
    }

private:
    std::vector<std::uint64_t> prefix_;
};
