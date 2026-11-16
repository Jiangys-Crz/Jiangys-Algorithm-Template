#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string a, b;
    if (!(std::cin >> a >> b)) return 0;

    auto i = a.size(), j = b.size();
    int carry = 0;
    std::string res;
    while (i || j || carry) {
        int sum = carry;
        if (i) sum += a[--i] - '0';
        if (j) sum += b[--j] - '0';
        res.push_back(static_cast<char>('0' + sum % 10));
        carry = sum / 10;
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    std::reverse(res.begin(), res.end());
    std::cout << res << '\n';
}
