#include <cstddef>
#include <string>

// In solve: strings pattern and text. matched is true if pattern is a subsequence.

std::size_t j = 0;
for (char c : text) {
    if (j < pattern.size() && c == pattern[j]) ++j;
}
bool matched = j == pattern.size();
