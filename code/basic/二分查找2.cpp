int l = 0, r = n;
while(l < r){
    int mid = l + (r - l + 1) / 2;
    if(a[mid] <= x) l = mid;
    else r = mid - 1;
}
cout << l << endl;