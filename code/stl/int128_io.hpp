#pragma once

#include <algorithm>
#include <optional>
#include <string>
#include <string_view>

#include "../types.hpp"

#if defined(__SIZEOF_INT128__)
inline std::string toString(lll x) {
    bool neg = x < 0;
    ulll val = static_cast<ulll>(x);
    if (neg) val = ulll{0} - val;
    std::string s;
    do {
        s.push_back(static_cast<char>('0' + val % 10));
        val /= 10;
    } while (val);
    if (neg) s.push_back('-');
    std::reverse(s.begin(), s.end());
    return s;
}

inline std::optional<lll> parseInt128(std::string_view s) {
    if (s.empty()) return std::nullopt;

    bool neg = s.front() == '-';
    if (neg || s.front() == '+') s.remove_prefix(1);
    if (s.empty()) return std::nullopt;

    constexpr ulll limit = ulll{1} << 127;
    ulll cap = neg ? limit : limit - 1, val = 0;
    for (char c : s) {
        if (c < '0' || c > '9') return std::nullopt;
        uint digit = c - '0';
        if (val > (cap - digit) / 10) return std::nullopt;
        val = val * 10 + digit;
    }
    if (val == limit) return -static_cast<lll>(limit - 1) - 1;
    return neg ? -static_cast<lll>(val) : static_cast<lll>(val);
}
#endif
