const double eps = 1e-8;
double l = 0, r = 1e6;
while(r - l > eps){
    double mid1 = l + (r - l) / 3.0;
    double mid2 = r - (r - l) / 3.0;
    if(mid1 == l || mid2 == r) break;

    if(calc(mid1) < calc(mid2)) l = mid1;
    else r = mid2;
}
double ans = (l + r) / 2.0;
cout << fixed << setprecision(10) << ans << endl;