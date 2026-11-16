// 先准备字符串 s。step 为最短周期，block 为最短完整重复块的长度。

int n = static_cast<int>(s.size());
vector<int> nxt(n);
for (int i = 1, j = 0; i < n; ++i) {
    while (j && s[i] != s[j]) j = nxt[j - 1];
    if (s[i] == s[j]) ++j;
    nxt[i] = j;
}
int step = n == 0 ? 0 : n - nxt.back();
int block = step && n % step == 0 ? step : n;
