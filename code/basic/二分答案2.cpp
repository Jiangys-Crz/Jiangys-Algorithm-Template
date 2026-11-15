ll l = 0, r = 1e18;
while(l < r){
    ll mid = l + (r - l + 1) / 2;
    if(check(mid)) l = mid;
    else r = mid - 1;
}
cout << l << endl;