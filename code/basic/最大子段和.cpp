#include <algorithm>

using ll = long long;

// a 为非空整数数组。

ll ending = a.front(), ans = ending;
for (size_t i = 1; i < a.size(); ++i) {
    ending = a[i] + max(0LL, ending);
    ans = max(ans, ending);
}
