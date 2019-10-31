#include<stdio.h>

#define CX 11
#define BASEMOD 1000000007
#define PHIE6 500000002
#define PHI502 243900800
#define MXN 100010
#define VAL 0
#define P2 1
#define P41 2
#define ull unsigned long long

int C[CX][CX];
int s2C[CX];
int fac[MXN*2][3];

int makeC() {
    for (int i=0; i<CX; ++i) {
        C[i][i] = C[i][0] = 1;
        for (int j=1; j<i; ++j) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
    
    for (int i=0; i<CX; ++i) {
        for (int j=0; j<CX; ++j) {
            s2C[i] += C[i][j]*C[i][j];
        }
    }
}

int bigmod(int base, ull exp, int mod) {
    if (exp==0) return 1;
    if (exp==1) return base;
    ull half = bigmod(base, exp>>1, mod);
    half *= half;
    
    if (exp&1) {
        return (int)(((half%mod) * base)%mod);
    }
    return (int)(half%mod);
}

int buildfac() {
    fac[0][VAL] = 1; // the rest
    fac[0][P2] = 0; //2^e
    fac[0][P41] = 0; //41^e
    
    for (int i=1; i<2*MXN; ++i) {
        for (int j=0; j<3; ++j) fac[i][j] = fac[i-1][j];
        
        int v = i;
        while (v%2 == 0) {
            v/=2;
            fac[i][P2]++;
        }
        
        while (v%41 == 0) {
            v/=41;
            fac[i][P41]++;
        }
        
        fac[i][VAL] = (int) (((ull)fac[i-1][VAL] * v)%PHIE6);
    }
}

int main() {
    buildfac();
    makeC();
    
    int T, a, b, N;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &a, &b, &N);
        if (a == 0 && b == 0) {
            printf("1\n");
            continue;
        }
        if (b == 0) {
            printf("1\n");
            continue;
        }
        if (a == 0) {
            printf("0\n");
            continue;
        }
        if (N == 0) {
            printf("%d\n", bigmod(a, b, BASEMOD));
            continue;
        }
        if (N < CX) {
            int be = bigmod(b, s2C[N], BASEMOD-1);
            printf("%d\n", bigmod(a, be, BASEMOD));
            continue;
        }
        
        int e2 = fac[2*N][P2] - 2*fac[N][P2];
        int e41 = fac[2*N][P41] - 2*fac[N][P41];
        ull hexp = ((ull)fac[2*N][VAL] * bigmod(fac[N][VAL], PHI502-2, PHIE6))%PHIE6;
        ull exp = (((ull)bigmod(2, e2, PHIE6) * (ull)bigmod(41, e41, PHIE6))%PHIE6 * hexp)%PHIE6;
        
        if (exp < 100) exp += PHIE6;
        
        int be = bigmod(b, exp, BASEMOD-1);
        printf("%d\n", bigmod(a, be, BASEMOD));
    }
}
