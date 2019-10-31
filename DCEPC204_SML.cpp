#include<stdio.h>

#define MOD 1000000000
#define ull unsigned long long
#define MXZ 22

ull F[MXZ];

int links[6][6] = {
    {-1,0,0,0,0,0},
    {1,2,3,4,5,-1},
    {1,3,5,-1,0,0},
    {1,2,4,5,-1,0},
    {1,3,5,-1,0,0},
    {1,2,3,4,-1,0},
};

int bigmod(int base,int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base;
    int half = bigmod(base, exp>>1, mod);
    
    if (exp&1) {
        return (int)(((((ull)half*half)%mod)*base)%mod);
    } else {
        return (int)(((ull)half*half)%mod);
    }
}

inline int max(int a, int b) {
    return (a>b)?a:b;
}

int main() {
    
    F[0] = F[1] = F[2] = 1;
    F[3] = F[4] = 3;
    F[5] = F[6] = 15;
    F[7] = F[8] = F[9] = F[10] = 105;
    
    for (int i=11; i<MXZ; ++i) {
        int e2 = (i%4) ? i/4+1 : i/4;
        int e3 = (i%5) ? i/5+1 : i/5;
        int e4 = (i%10)? i/10+1:i/10;
        
        F[i] = (1LL<<e2) * F[e3] * F[e4];
    }
    
    int t, N;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        if (N>=21) printf("0\n");
        else {
            int zmax = 0;
            for (int x=1; x<=5; ++x) {
                for (int i=0; links[x][i]>0; ++i) {
                    zmax = max(zmax, bigmod(x*F[N], links[x][i]*F[N], MOD));
                }
            }
            printf("%d\n", zmax);
        }
    }
    
}