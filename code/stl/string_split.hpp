#pragma once

#include <string>
#include <vector>

inline std::vector<std::string> split(const std::string& s, char sep) {
    std::vector<std::string> res;
    auto l = std::string::size_type{0};
    while (true) {
        auto r = s.find(sep, l);
        if (r == std::string::npos) {
            res.push_back(s.substr(l));
            return res;
        }
        res.push_back(s.substr(l, r - l));
        l = r + 1;
    }
}
