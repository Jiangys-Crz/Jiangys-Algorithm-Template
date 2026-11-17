constexpr int inf = 1000000000;

struct FHQTreap {
    // 节点定义 (根据题目要求修改)
    struct Node {
        int l, r;       // 左右孩子索引
        int val;        // 节点数值
        int sz;         // 子树大小
        unsigned int key; // 随机权值
		// 其他信息，如懒标记等

		ll sum;
		ll lazy;
    };

    std::vector<Node> tr;
    int root;
    int idx; // 内存池计数器
    std::mt19937 rnd; // 随机数生成器

    // 初始化：预估最大节点数 N
    FHQTreap(int N) {
        tr.resize(N + 1);
        root = 0;
        idx = 0;
        rnd.seed(std::chrono::steady_clock::now().time_since_epoch().count());
		// 初始化其他信息
    }

    // 新建节点 (根据题目要求修改)
    int new_node(int v) {
        int u = ++idx;
        tr[u].l = tr[u].r = 0;
        tr[u].val = v;
        tr[u].sz = 1;
        tr[u].key = rnd();
		// 其他信息
        return u;
    }

    // 向上更新 (Push Up)
    // 用子节点的信息更新父节点 (类似线段树)
    void push_up(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
        
    }

    // 向下下传 (Push Down)
    // 处理懒标记 (Lazy Tag)
    void push_down(int u) {
        
    }

    // 分裂 (Split)
    // 按值 v 分裂：x 树全部 <= v，y 树全部 > v
    void split(int u, int v, int &x, int &y) {
        if (!u) {
            x = y = 0;
            return;
        }
        push_down(u);
        if (tr[u].val <= v) {
            x = u;
            split(tr[u].r, v, tr[u].r, y);
        } else {
            y = u;
            split(tr[u].l, v, x, tr[u].l);
        }
        push_up(u);
    }

    // 按排名 Split (处理区间翻转等问题用)
    void split_by_rank(int u, int k, int &x, int &y) {
        if (!u) { x = y = 0; return; }
        push_down(u);
        int left_sz = tr[tr[u].l].sz + 1;
        if (left_sz <= k) {
            x = u;
            split_by_rank(tr[u].r, k - left_sz, tr[u].r, y);
        } else {
            y = u;
            split_by_rank(tr[u].l, k, x, tr[u].l);
        }
        push_up(u);
	}

    // 合并 (Merge) 
    // 将 x 和 y 合并，要求 x 所有值 <= y 所有值
    int merge(int x, int y) {
        if (!x || !y) return x | y;
        push_down(x);
        push_down(y);
        
        if (tr[x].key < tr[y].key) {
            tr[x].r = merge(tr[x].r, y);
            push_up(x);
            return x;
        } else {
            tr[y].l = merge(x, tr[y].l);
            push_up(y);
            return y;
        }
    }

    // 插入数值 v
    void insert(int v) {
        int x, y;
        split(root, v, x, y);
        root = merge(merge(x, new_node(v)), y);
    }

    // 删除数值 v
    void erase(int v) {
        int x, y, z;
        split(root, v, x, z);
        split(x, v - 1, x, y);
        if (y) y = merge(tr[y].l, tr[y].r);
        root = merge(merge(x, y), z);
    }

    // 查询 v 的排名 (比 v 小的数的个数 + 1)
    int get_rank(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int ans = tr[x].sz + 1;
        root = merge(x, y);
        return ans;
    }

    // 根据排名查数值 (第 k 小)
    int get_val_by_rank(int u, int k) {
        if (k > tr[u].sz) return -1;
        while (true) {
            push_down(u);
            int left_sz = tr[tr[u].l].sz + 1;
            if (k == left_sz) return tr[u].val;
            if (k < left_sz) {
                u = tr[u].l;
            } else {
                k -= left_sz;
                u = tr[u].r;
            }
        }
    }
    
    // 查找 v 的前驱 (小于 v 的最大值)
    int get_prev(int v) {
        int x, y;
        split(root, v - 1, x, y);
        if (!x) return -inf; // 不存在
        int u = x;
        while (tr[u].r) u = tr[u].r; // 也就是 x 树里最右边的那个
        int res = tr[u].val;
        root = merge(x, y);
        return res;
    }

    // 查找 v 的后继 (大于 v 的最小值)
    int get_next(int v) {
        int x, y;
        split(root, v, x, y);
        if (!y) return inf; // 不存在
        int u = y;
        while (tr[u].l) u = tr[u].l; // 也就是 y 树里最左边的那个
        int res = tr[u].val;
        root = merge(x, y);
        return res;
    }
};