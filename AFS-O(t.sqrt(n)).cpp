#include<stdio.h>#define ll long longint main() {    int t, n;    scanf("%d", &t);    while(t--) {        scanf("%d", &n);                ll sum = n-1;        int lasti;        for (int i=2; i*i<=n; ++i) {            sum += (n/i-1)*i;            lasti = i;        }                for (int i=2; i*i<n; ++i) {            sum += (ll)(n/i-lasti)*(n/i+lasti+1)/2;        }                printf("%lld\n", sum);    }    return 0;}