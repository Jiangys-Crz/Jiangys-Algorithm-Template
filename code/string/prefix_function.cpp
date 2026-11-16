// 先准备字符串 s。nxt[i] 为位置 i 的前缀函数值。

int n = static_cast<int>(s.size());
vector<int> nxt(n);
for (int i = 1, j = 0; i < n; ++i) {
    while (j && s[i] != s[j]) j = nxt[j - 1];
    if (s[i] == s[j]) ++j;
    nxt[i] = j;
}
