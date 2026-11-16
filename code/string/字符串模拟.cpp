#include <algorithm>
#include <string>

// 先准备非空十进制数字串 a 和 b。res 保存两数之和。

auto i = a.size(), j = b.size();
int carry = 0;
string res;
while (i || j || carry) {
    int sum = carry;
    if (i) sum += a[--i] - '0';
    if (j) sum += b[--j] - '0';
    res.push_back(static_cast<char>('0' + sum % 10));
    carry = sum / 10;
}
while (res.size() > 1 && res.back() == '0') res.pop_back();
reverse(res.begin(), res.end());
