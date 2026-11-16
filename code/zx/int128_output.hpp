#include <algorithm>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

using uint = unsigned int;

#if defined(__SIZEOF_INT128__)
__extension__ using lll = __int128;
__extension__ using ulll = unsigned __int128;
#endif

#ifndef XCPC_STL_INT128_IO_HPP
#define XCPC_STL_INT128_IO_HPP

#if defined(__SIZEOF_INT128__)
inline string toString(lll x) {
    bool neg = x < 0;
    ulll val = static_cast<ulll>(x);
    if (neg) val = ulll{0} - val;
    string s;
    do {
        s.push_back(static_cast<char>('0' + val % 10));
        val /= 10;
    } while (val);
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

inline optional<lll> parseInt128(string_view s) {
    if (s.empty()) return nullopt;

    bool neg = s.front() == '-';
    if (neg || s.front() == '+') s.remove_prefix(1);
    if (s.empty()) return nullopt;

    constexpr ulll limit = ulll{1} << 127;
    ulll cap = neg ? limit : limit - 1, val = 0;
    for (char c : s) {
        if (c < '0' || c > '9') return nullopt;
        uint digit = c - '0';
        if (val > (cap - digit) / 10) return nullopt;
        val = val * 10 + digit;
    }
    if (val == limit) return -static_cast<lll>(limit - 1) - 1;
    return neg ? -static_cast<lll>(val) : static_cast<lll>(val);
}
#endif

#endif

#ifndef XCPC_ZX_INT128_OUTPUT_HPP
#define XCPC_ZX_INT128_OUTPUT_HPP

#if defined(__SIZEOF_INT128__)
inline ostream& operator<<(ostream& out, lll x) {
    return out << toString(x);
}
#endif

#endif
