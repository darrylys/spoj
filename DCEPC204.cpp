#include<stdio.h>
#include<math.h>

#define MXF 22
#define MOD 1000000000
#define PHIMOD 400000000
#define ull unsigned long long

int max(int a, int b) {
    return (a>b)?a:b;
}

int F[MXF][8];
int prime[4] = {2,3,5,7};

int links[6][6] = {
    {-1,0,0,0,0,0},
    {1,2,3,4,5,-1},
    {1,3,5,-1,0,0},
    {1,2,4,5,-1,0},
    {1,3,5,-1,0,0},
    {1,2,3,4,-1,0},
};

void initF() {
    F[3][3] = 1;
    F[4][3] = 1;
    
    F[5][3] = F[5][5] = 1;
    F[6][3] = F[6][5] = 1;
    
    F[7][3] = F[7][5] = F[7][7] = 1;
    F[8][3] = F[8][5] = F[8][7] = 1;
    F[9][3] = F[9][5] = F[9][7] = 1;
    F[10][3] = F[10][5] = F[10][7] = 1;
}

//F(n) = (2^(n/4)) * F(n/5)* F(n/10)      (for n>10)
void fillF() {
    for (int i=11; i<MXF; ++i) {
        int e2 = (i%4) ? i/4+1 : i/4;
        int e3 = (i%5) ? i/5+1 : i/5;
        int e4 = (i%10)? i/10+1:i/10;
        
        F[i][2] = e2 + F[e3][2] + F[e4][2];
        F[i][3] = F[e3][3] + F[e4][3];
        F[i][5] = F[e3][5] + F[e4][5];
        F[i][7] = F[e3][7] + F[e4][7];
    }
}

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

int getFNmodphi106(int N) {
    ull mul = 1;
    for (int i=0; i<4; ++i) {
        mul = (mul * bigmod(prime[i], F[N][prime[i]], PHIMOD))%PHIMOD;
    }
    return (int)mul;
}

int getFNeFN(int N, int FNmodPhi) {
    int zi[4];
    
    //3&7
    zi[1] = (int)(((ull)F[N][3]*FNmodPhi)%PHIMOD);
    zi[3] = (int)(((ull)F[N][7]*FNmodPhi)%PHIMOD);
    
    //2%5
    ull t = (ull)F[N][2]*FNmodPhi;
    if (t<26) zi[0] = t;
    else {
        zi[0] = (int)(t%PHIMOD);
        if (zi[0] < 26) zi[0] += PHIMOD;
    }
    
    t = (ull)F[N][5]*FNmodPhi;
    if (t<26) zi[2] = t;
    else {
        zi[2] = (int)(t%PHIMOD);
        if (zi[2] < 26) zi[2] += PHIMOD;
    }
    
    ull mul = 1;
    for (int i=0; i<4; ++i) {
        mul = (mul * bigmod(prime[i], zi[i], MOD))%MOD;
    }
    return (int)mul;
}

int xpytFN(int N, int FNmodPhi, int x, int y) {
    int mx = bigmod(x, FNmodPhi, MOD);
    return bigmod(mx, y, MOD);
}

int FNeFNty(int FNeFN, int y) {
    return bigmod(FNeFN, y, MOD);
}

int main() {
    initF();
    fillF();
    
    int t,N;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        
        if (N>=21) {
            printf("0\n");
            continue;
        }
        
        int FNmodPhi = getFNmodphi106(N);
        int FNeFN = getFNeFN(N, FNmodPhi);
        /*
        printf("FN mod PHI(10^9)=%d, FN^FN=%d\n", FNmodPhi, FNeFN);
        printf("F(%d)=2^%d * 3^%d * 5^%d * 7^%d\n", N, F[N][2], F[N][3], F[N][5], F[N][7]);
        */
        int zmax = 0;
        for (int x=1; x<=5; ++x) {
            for (int i=0, y, t; links[x][i]>0; ++i) {
                y = links[x][i];
                t = (int)(((ull)FNeFNty(FNeFN, y) * xpytFN(N, FNmodPhi, x, y))%MOD);
          //      printf("x=%d, y=%d, t=%d\n", x, y, t);
                zmax = max(zmax, t);
            }
        }
        printf("%d\n", zmax);
    }
    return 0;
}
