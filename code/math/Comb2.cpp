Z C(int a, int b) {
	Z res = 1;
    for (int i = 1, j = a; i <= b; i++, j--)
    {
        res = res * j;
        res = res / i;
    }
    return res;
}