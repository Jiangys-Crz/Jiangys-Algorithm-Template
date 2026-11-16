#include <iterator>
#include <set>

using ll = long long;

// 先准备多重集合 s 和待删值 x，至多删除一份 x。

auto it = s.find(x);
if (it != s.end()) s.erase(it);

auto l = s.lower_bound(x);
auto r = s.upper_bound(x);
// 若 l != s.begin()，则严格前驱为 *prev(l)。
// 若 r != s.end()，则严格后继为 *r。
