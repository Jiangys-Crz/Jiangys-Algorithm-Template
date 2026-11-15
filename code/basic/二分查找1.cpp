int l = 1, r = n + 1;
while(l < r){
    int mid = l + (r - l) / 2;
    if(a[mid] >= x) r = mid;
    else l = mid + 1;
}
cout << l << endl;