#include<stdio.h>

#define ll long long

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    if (k>=n) printf("%lld\n", n*2-1);
    else {
        ll zum = n*n - k*(k+1);
        printf("%lld\n", k*2 +zum/k + (zum%k!=0));
    }
}