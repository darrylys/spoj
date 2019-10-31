#include<stdio.h>

#define ull unsigned long long
#define MOD 1000000000
#define PHIMOD 400000000

#define MX 130

int F[MX][8];

int FACT[MX]={1,1,1,1,1,2,2,3,3,2,3,3,5,5,3,5,5,5,6,7,8,8,9,6,7,10,9,10,11,8,
10,8,11,9,12,10,11,13,17,13,10,16,14,14,13,14,17,12,15,15,20,19,19,18,19,19,
18,21,18,20,20,2,21,22,21,21,24,23,1,22,21,1,24,11,24,1,25,8,1,5,3,3,4,6,3,
12,4,3,4,10,4,5,5,8,13,8,12,2,11,4,6,11,13,12,9,21,12,18,17,15,14,15,14,11,
23,2,20,23,16,18,21,23,3,18,4,23,3,5,1,24};

int links[6][6] = {
    {-1,0,0,0,0,0},
    {1,2,3,4,5,-1},
    {1,3,5,-1,0,0},
    {1,2,4,5,-1,0},
    {1,3,5,-1,0,0},
    {1,2,3,4,-1,0},
};

int bigmod(int base, int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base;
    ull half = bigmod(base, exp>>1, mod);
    half = (((ull)half*half)%mod);
    if (exp&1) {
        half = (half*base)%mod;
    }
    return (int)half;
}

inline int max(int a, int b) {
    return (a>b)?a:b;
}

int spbigmod(int base, int _2Limexp, int _restExp, int mod) {
    if (_2Limexp == 0 && _restExp == 0) return 1;
    else if (_2Limexp == 0 && _restExp == 1) return base;
    int half;
    if (_2Limexp) {
        half = spbigmod(base, _2Limexp-1, _restExp, mod);
        return (int)(((ull)half*half)%mod);
    } else {
        half = spbigmod(base, 0, _restExp>>1, mod);
        ull r = ((ull)half*half)%mod;
        if (_restExp&1) {
            r = (r*base)%mod;
        }
        return (int)r;
    }
    
}

void build() {
    for (int i=0; i<MX; ++i) {
        int m = 5, v = i;
        FACT[i] = 0;
        while (m<v) {
            FACT[i] += v/m;
            m *=5;
        }
        
        FACT[i] = (FACT[i]%25 + 1);
        //printf("FACT[%d]=%d\n", i, FACT[i]);
    }

    //build
    F[3][3] = 1;
    F[4][3] = 1;
    
    F[5][3] = F[5][5] = 1;
    F[6][3] = F[6][5] = 1;
    
    F[7][3] = F[7][5] = F[7][7] = 1;
    F[8][3] = F[8][5] = F[8][7] = 1;
    F[9][3] = F[9][5] = F[9][7] = 1;
    F[10][3] = F[10][5] = F[10][7] = 1;
    
    // ier
    for (int i=11; i<MX; ++i) {
        F[i][2] = 2*FACT[i] + F[i/5][2] + F[i/10][2];
        F[i][3] = F[i/5][3] + F[i/10][3];
        F[i][5] = F[i/5][5] + F[i/10][5];
        F[i][7] = F[i/5][7] + F[i/10][7];
    }
    

}

int main() {
    build();
    
    int t, N;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        
        if (N>=MX) printf("0\n");
        else {
            ull sA = bigmod(2, F[N][2], MOD);
            
            ull non2 = bigmod(3, F[N][3], MOD);
            non2 = (non2 * bigmod(5, F[N][5], MOD))%MOD;
            non2 = (non2 * bigmod(7, F[N][7], MOD))%MOD;
            
            ull axFN = (sA * non2)%MOD;
            
            int zmax = 0;
            int restexp=non2, _2e=F[N][2];
            
            //printf("axFN=%llu\n", axFN);
            
            for (int i=1; i<=5; ++i) {
                for (int j=0; links[i][j] > 0; ++j) {
                    switch (links[i][j]) {
                        case 1: restexp=non2; _2e=F[N][2]; break;
                        case 2: restexp=non2; _2e=F[N][2]+1; break;
                        case 3: restexp=non2*3; _2e=F[N][2]; break;
                        case 4: restexp=non2; _2e=F[N][2]+2; break;
                        case 5: restexp=non2*5; _2e=F[N][2]; break;
                    }
                    
                    int zv = spbigmod((int)((i * axFN) % MOD), _2e, restexp, MOD);
                    zmax = max(zmax, zv);
                    //printf("[%d,%d] restexp=%d, _2e=%d, zmax=%d\n", i, links[i][j], restexp, _2e, zv);
                }
            }
            
            printf("%d\n", zmax);
        }
    }
    return 0;
}
