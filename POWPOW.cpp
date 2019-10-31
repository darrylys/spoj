#include<stdio.h>

#define FML 500000003
#define MOD 1000000006
#define MXN 100010
#define INV2 250000002
#define ull unsigned long long

int fac[MXN<<1];

int bigmod(int base, int exp, int mod) {
    if (exp==0) return 1;
    if (exp==1) return base;
    ull half = bigmod(base, exp>>1, mod);
    half *= half;
    
    if (exp&1) {
        return (int)(((half%mod) * base)%mod);
    }
    return (int)(half%mod);
}

void buildfac() {
    fac[0] = 1;
    for(int i=1; i<MXN<<1; ++i) {
        fac[i] = (int)(((ull)fac[i-1]*i)%FML);
    }
}

int main() {
    buildfac();
    
    int T, a, b, N;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &a, &b, &N);
        if (N == 0 || b == 0 || a == 0) {
            printf("%d\n", a);
            continue;
        }
        
        ull a2 = ((ull)fac[2*N] * bigmod(fac[N], FML-3, FML))%FML;
        ull exp = ((a2<<1)*INV2)%MOD;
        
        ull aexp = bigmod(exp, b, MOD);
        ull res = bigmod(a, aexp, MOD+1);
        printf("%llu\n", res);
    }
    return 0;
}
