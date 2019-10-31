#include<stdio.h>

#define ll long long

ll a[2020];

int main() {
    int n, m;
    
    scanf("%d%d\n", &n, &m);
    
    a[0] = a[1] = 1;
    a[2] = a[3] = 0;
    
    for (int i=4; i<=n; ++i) {
        a[i] = ((i+1) * a[i-1]) % m;
        a[i] = (a[i]+m - ((i-2)*a[i-2])%m + (ll)m)%m;
        a[i] = (a[i]+m - ((i-5)*a[i-3])%m + (ll)m)%m;
        a[i] = (a[i] + ((i-3)*a[i-4])%m )%m;
        
        //printf("set=%lld\n", a[i]);
    }
    
    printf("%lld\n", a[n]%m);
}