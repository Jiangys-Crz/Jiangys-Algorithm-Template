#include <cstddef>
#include <string>

// In solve: string s and char sep. Empty fields are preserved.

for (std::size_t l = 0; ; ) {
    auto r = s.find(sep, l);
    auto field = s.substr(l, r == std::string::npos ? r : r - l);
    // TODO: Process field, including empty fields.
    if (r == std::string::npos) break;
    l = r + 1;
}
