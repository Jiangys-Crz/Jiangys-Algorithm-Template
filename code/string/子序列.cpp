#include <cstddef>
#include <string_view>

bool isSubsequence(std::string_view pattern, std::string_view text) {
    std::size_t j = 0;
    for (char c : text) {
        if (j < pattern.size() && c == pattern[j]) ++j;
    }
    return j == pattern.size();
}
