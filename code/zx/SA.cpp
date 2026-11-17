/*
 * 模拟退火模板
 * --------------------------------------------
 * 可复用特点：
 *  - 封装良好：只需改 energy() 即可换题
 *  - 可调参数（温度、衰减率、循环次数）
 *  - 自动记录最优解
 *  - 输出最优能量
 */

struct SA {
    std::vector<double> xs, ys;
    double best_x, best_val;

	SA(){}
	SA(int n) {
		xs.resize(n);
		ys.resize(n);
	}

    // 能量函数（目标函数）
    double energy(double t) {
        double res = 0;
        for (int i = 0; i < (int)xs.size(); i++) {
            double dx = t - xs[i];
            res = std::max(res, dx * dx + ys[i] * ys[i]);
        }
        return sqrt(res);
    }

    // 主过程
    void run(double init_T = 1e4, double end_T = 1e-3, double alpha = 0.97, int iter_per_T = 50) {
        double minx = *min_element(xs.begin(), xs.end());
        double maxx = *max_element(xs.begin(), xs.end());
        double t = (minx + maxx) / 2;
        double val = energy(t);
        best_x = t;
        best_val = val;

        double T = init_T;
        auto rnd = []() { return (rand() / (double)RAND_MAX) * 2 - 1; };

        while (T > end_T) {
            for (int i = 0; i < iter_per_T; ++i) {
                double t2 = t + rnd() * T;  // 随机扰动
                double val2 = energy(t2);
                double delta = val2 - val;
                // 接受策略
                if (delta < 0 || exp(-delta / T) > rand() / (double)RAND_MAX) {
                    t = t2;
                    val = val2;
                    if (val < best_val) {
                        best_val = val;
                        best_x = t;
                    }
                }
            }
            T *= alpha;
        }
    }
};