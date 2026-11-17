double ans = 0;
// 特判在一条直线上
if (res.back() == res[res.size() - 2]) {
    ans = 2 * dis(a[0], a[n - 1]);
} else {
    for (int i = 1; i < res.size(); i++) {
        ans += dis(a[res[i]], a[res[i - 1]]);
    }
}