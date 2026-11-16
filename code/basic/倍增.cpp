class BinaryJump {
public:
    explicit BinaryJump(const vector<int>& next) : up_(levels, next) {
        for (int k = 1; k < levels; ++k) {
            for (size_t v = 0; v < next.size(); ++v) {
                up_[k][v] = up_[k - 1][up_[k - 1][v]];
            }
        }
    }

    int jump(int v, uint64_t steps) const {
        for (int k = 0; steps != 0; ++k, steps >>= 1) {
            if (steps & 1) {
                v = up_[k][v];
            }
        }
        return v;
    }

private:
    static constexpr int levels = numeric_limits<uint64_t>::digits;
    vector<vector<int>> up_;
};
