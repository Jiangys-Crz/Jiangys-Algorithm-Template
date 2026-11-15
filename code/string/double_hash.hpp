#include <cstddef>
#include <cstdint>
#include <string_view>
#include <utility>
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

#ifndef XCPC_STRING_DOUBLE_HASH_HPP
#define XCPC_STRING_DOUBLE_HASH_HPP

struct DoubleHash {
    using Value = std::pair<std::uint32_t, std::uint32_t>;
    RollingHash<1000000007, 911382323> h1;
    RollingHash<1000000009, 972663749> h2;

    explicit DoubleHash(std::string_view s) : h1(s), h2(s) {}

    Value get() const {
        return {h1.get(), h2.get()};
    }

    Value substring(std::size_t l, std::size_t r) const {
        return {h1.substring(l, r), h2.substring(l, r)};
    }

    Value replaced(std::size_t i, unsigned char c) const {
        return {h1.replaced(i, c), h2.replaced(i, c)};
    }
};

#endif
