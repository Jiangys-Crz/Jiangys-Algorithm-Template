#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

class BinaryJump {
public:
    explicit BinaryJump(const std::vector<int>& next) : up_(levels, next) {
        for (int k = 1; k < levels; ++k) {
            for (std::size_t v = 0; v < next.size(); ++v) {
                up_[k][v] = up_[k - 1][up_[k - 1][v]];
            }
        }
    }

    int jump(int v, std::uint64_t steps) const {
        for (int k = 0; steps != 0; ++k, steps >>= 1) {
            if (steps & 1) {
                v = up_[k][v];
            }
        }
        return v;
    }

private:
    static constexpr int levels = std::numeric_limits<std::uint64_t>::digits;
    std::vector<std::vector<int>> up_;
};
