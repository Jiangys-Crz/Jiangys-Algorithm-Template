#ifndef XCPC_STRING_ROLLING_HASH_HPP
#define XCPC_STRING_ROLLING_HASH_HPP

template<uint32_t Mod = 1000000007, uint32_t Base = 911382323>
class RollingHash {
    static_assert(256 < Base && Base < Mod);
    using U64 = uint64_t;

public:
    explicit RollingHash(string_view s)
        : pre(s.size() + 1), pw(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); ++i) {
            pre[i + 1] = (U64(pre[i]) * Base + code(s[i])) % Mod;
            pw[i + 1] = U64(pw[i]) * Base % Mod;
        }
    }

    uint32_t get() const {
        return pre.back();
    }

    uint32_t substring(size_t l, size_t r) const {
        return (U64(pre[r]) + Mod - U64(pre[l]) * pw[r - l] % Mod) % Mod;
    }

    uint32_t replaced(size_t i, unsigned char c) const {
        U64 delta = (U64(code(c)) + Mod - substring(i, i + 1)) % Mod;
        return (U64(get()) + delta * pw[pre.size() - 2 - i] % Mod) % Mod;
    }

private:
    vector<uint32_t> pre, pw;

    static uint32_t code(unsigned char c) {
        return static_cast<uint32_t>(c) + 1;
    }
};

#endif
