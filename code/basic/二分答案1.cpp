ll l = 0, r = 1e18;
while(l < r){
    ll mid = l + (r - l) / 2;
    if(check(mid)) r = mid;
    else l = mid + 1;
}
cout << l << endl;