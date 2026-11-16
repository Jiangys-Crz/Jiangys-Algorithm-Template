#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string s;
    if (!std::getline(std::cin, s)) return 0;
    if (s.empty()) {
        std::cout << "0 0\n";
        return 0;
    }
    int n = static_cast<int>(s.size());
    std::vector<int> nxt(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = nxt[j - 1];
        if (s[i] == s[j]) ++j;
        nxt[i] = j;
    }
    int p = n - nxt.back();
    std::cout << p << ' ' << (n % p == 0 ? p : n) << '\n';
}
