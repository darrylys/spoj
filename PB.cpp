#include<stdio.h>

#define MOD 10007

int bigmod(int base, int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base;
    
    int a = bigmod(base, exp/2, mod);
    if (exp % 2 == 1) {
        return (((base*a)%mod) * a)%mod;
    } else {
        return (a*a)%mod;
    }
}

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", bigmod((n+1)%MOD, n-1, MOD));
    }
    return 0;
}