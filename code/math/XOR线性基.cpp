#include <array>
#include <cstdint>

class XorBasis {
public:
    bool insert(uint64_t value) {
        for (int bit = 63; bit >= 0; --bit) {
            if (((value >> bit) & 1) == 0) {
                continue;
            }
            if (pivot_[bit] == 0) {
                pivot_[bit] = value;
                return true;
            }
            value ^= pivot_[bit];
        }
        return false;
    }

    bool contains(uint64_t value) const {
        for (int bit = 63; bit >= 0; --bit) {
            if (((value >> bit) & 1) == 0) {
                continue;
            }
            if (pivot_[bit] == 0) {
                return false;
            }
            value ^= pivot_[bit];
        }
        return true;
    }

    uint64_t maximum() const {
        uint64_t answer = 0;
        for (int bit = 63; bit >= 0; --bit) {
            const uint64_t candidate = answer ^ pivot_[bit];
            if (candidate > answer) {
                answer = candidate;
            }
        }
        return answer;
    }

private:
    array<uint64_t, 64> pivot_{};
};
