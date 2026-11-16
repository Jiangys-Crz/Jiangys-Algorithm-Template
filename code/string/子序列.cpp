#include <cstddef>
#include <string>

// 先准备模式串 pattern 和文本 text。matched 表示模式串是否为文本的子序列。

size_t j = 0;
for (char c : text) {
    if (j < pattern.size() && c == pattern[j]) ++j;
}
bool matched = j == pattern.size();
