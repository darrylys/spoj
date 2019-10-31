#include<stdio.h>

#define ull unsigned long long
#define MOD 1000000007
#define MXN 2000002

int fac[MXN];

int bigmod(int base, int exp, int mod) {
    if (base == 0) return 0;
    if (base == 1) return 1;
    if (exp == 0) return 1;
    if (exp == 1) return base;
    
    ull half = bigmod(base, exp>>1, mod);
    ull h2 = (half*half)%mod;
    if (exp&1) {
        h2 = (h2*base)%mod;
    }
    return (int)h2;
}

void buildfac() {
    fac[0]=1;
    for (int i=1; i<MXN; ++i) {
        fac[i] = ((ull)fac[i-1]*i)%MOD;
    }
}

int main() {
    int inv2 = bigmod(2, MOD-2, MOD);
    buildfac();
    
    int t, n, invnf2;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        invnf2 = bigmod(fac[n], MOD-3, MOD);
        ull res = ((((ull)inv2 * n)%MOD * fac[2*n])%MOD * invnf2) %MOD;
        printf("%llu\n", res);
    }
    return 0;
}
