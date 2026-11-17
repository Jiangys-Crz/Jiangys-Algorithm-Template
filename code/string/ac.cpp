// Trie+Kmp，多模式串匹配
struct ACAutomaton {
    static constexpr int N = 1E6 + 10;
    std::vector<int> fail, cnt;
    std::vector<std::vector<int>> ch;
    int cntNodes;

    ACAutomaton() {
        ch.resize(N, std::vector<int>(26));
        fail.resize(N);
        cnt.resize(N);
        cntNodes = 0;
    }
    void insert(std::string &s) {
        int u = 0;
        for (auto c : s) {
            int &v = ch[u][c - 'a'];
            if (!v) v = ++cntNodes;
            u = v;
        }
        cnt[u]++;
    }
    void build() {
        std::queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (ch[0][i]) {
                q.push(ch[0][i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                int &v = ch[u][i];
                if (!v) {
                    v = ch[fail[u]][i];
                } else {
                    fail[v] = ch[fail[u]][i];
                    q.push(v);
                }
            }
        }
    }
    ll query(std::string &t) {
        ll ans = 0;
        int u = 0;
        for (auto c : t) {
            u = ch[u][c - 'a'];
            for (int v = u; v && ~cnt[v]; v = fail[v]) {
                ans += cnt[v];
                cnt[v] = -1;
            }
        }
        return ans;
    }
};