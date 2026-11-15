const double eps = 1e-8;
double l = 0, r = 1e9;
while(r - l > eps){
    double mid = l + (r - l) / 2.0;
    if(check(mid)) l = mid;
    else r = mid;
}
cout << fixed << setprecision(10) << l << endl;