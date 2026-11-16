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

#ifndef XCPC_STRING_DOUBLE_HASH_HPP
#define XCPC_STRING_DOUBLE_HASH_HPP

struct DoubleHash {
    using Value = pair<uint32_t, uint32_t>;
    RollingHash<1000000007, 911382323> h1;
    RollingHash<1000000009, 972663749> h2;

    explicit DoubleHash(string_view s) : h1(s), h2(s) {}

    Value get() const {
        return {h1.get(), h2.get()};
    }

    Value substring(size_t l, size_t r) const {
        return {h1.substring(l, r), h2.substring(l, r)};
    }

    Value replaced(size_t i, unsigned char c) const {
        return {h1.replaced(i, c), h2.replaced(i, c)};
    }
};

#endif

vector<int> rabinKarp(string_view s, string_view t) {
    vector<int> ans;
    auto m = t.size();
    if (m > s.size()) return ans;

    DoubleHash hs(s), ht(t);
    auto target = ht.get();
    for (size_t l = 0; l <= s.size() - m; ++l) {
        if (hs.substring(l, l + m) == target && s.substr(l, m) == t) {
            ans.push_back(static_cast<int>(l));
        }
    }
    return ans;
}
