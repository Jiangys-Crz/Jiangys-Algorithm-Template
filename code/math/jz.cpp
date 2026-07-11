template<class T>
struct Matrix {
	std::vector<std::vector<T>> matrix;
	int n;
	Matrix(int _n): n(_n) {
		matrix.assign(n, std::vector<T>(n, 0));
	}
	static Matrix getIdentity(int n) {
		Matrix res(n);
		for (int i = 0; i < n; i++) {
			res.matrix[i][i] = 1;
		}
		return res;
	}
	constexpr Matrix operator*(const Matrix &b) const {
		Matrix res(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					res.matrix[i][j] += matrix[i][k] * b.matrix[k][j];
				}
			}
		}
		return res;
	}
};

template<class T>
Matrix<T> pow(Matrix<T> base, i64 b) {
	Matrix<T> res = Matrix<T>::getIdentity(base.n);
	while (b) {
		if (b & 1) res = res * base;
		b >>= 1;
		base = base * base;
	}
	return res;
}