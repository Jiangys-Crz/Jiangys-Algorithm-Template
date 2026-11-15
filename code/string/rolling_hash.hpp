#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

#ifndef XCPC_STRING_ROLLING_HASH_HPP
#define XCPC_STRING_ROLLING_HASH_HPP

template<std::uint32_t Mod = 1000000007, std::uint32_t Base = 911382323>
class RollingHash {
    static_assert(256 < Base && Base < Mod);
    using U64 = std::uint64_t;

public:
    explicit RollingHash(std::string_view s)
        : pre(s.size() + 1), pw(s.size() + 1, 1) {
        for (std::size_t i = 0; i < s.size(); ++i) {
            pre[i + 1] = (U64(pre[i]) * Base + code(s[i])) % Mod;
            pw[i + 1] = U64(pw[i]) * Base % Mod;
        }
    }

    std::uint32_t get() const {
        return pre.back();
    }

    std::uint32_t substring(std::size_t l, std::size_t r) const {
        return (U64(pre[r]) + Mod - U64(pre[l]) * pw[r - l] % Mod) % Mod;
    }

    std::uint32_t replaced(std::size_t i, unsigned char c) const {
        U64 delta = (U64(code(c)) + Mod - substring(i, i + 1)) % Mod;
        return (U64(get()) + delta * pw[pre.size() - 2 - i] % Mod) % Mod;
    }

private:
    std::vector<std::uint32_t> pre, pw;

    static std::uint32_t code(unsigned char c) {
        return static_cast<std::uint32_t>(c) + 1;
    }
};

#endif
