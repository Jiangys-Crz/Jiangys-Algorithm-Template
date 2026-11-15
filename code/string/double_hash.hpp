#pragma once

#include <utility>

#include "rolling_hash.hpp"

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
