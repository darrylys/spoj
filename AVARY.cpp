#include<stdio.h>
#include<string.h>

#define XN 550
#define MXN 120
#define ll long long int
#define BASE 1000000000

typedef struct {
    int c[MXN];
    int n;
} BGM;

BGM xsq[2];
char res[2][XN];
char pos[XN];

int e10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

inline int max(int a, int b) {
    return (a>b)?a:b;
}

inline int min(int a, int b) {
    return (a<b)?a:b;
}

void printBGM(BGM& a) {
    for (int i=a.n-1; i>=0; --i) {
        printf("%09d ", a.c[i]);
    }
    putchar('\n');
}

void initbgm(BGM& a, int n, int* arr) {
    for (int i=n-1; i>=0; --i) {
        a.c[n-i-1] = arr[i];
    }
    a.n = n;
}

void add(BGM& a, BGM& b, BGM& result) {
    int carry = 0;
    ll temp;
    int l = max(a.n, b.n);
    for (int i=0; i<l; ++i) {
        temp = (ll)a.c[i] + b.c[i] + carry;
        result.c[i] = temp%BASE;
        carry = temp/BASE;
    }
    result.c[l] = carry;
    result.n = l + (carry>0);
}

void singledigitmul(BGM& a, int d, BGM& result) { //d == single digit!
    int carry = 0;
    ll temp;
    for (int i=0; i<a.n; ++i) {
        temp = (ll)a.c[i] * d + carry;
        result.c[i] = temp%BASE;
        carry = temp/BASE;
    }
    result.c[a.n] = carry;
    result.n = a.n + (carry>0);
}

void appendzeroX2(int azero, BGM& x, BGM& result) {
    memset(result.c, 0, sizeof(result.c));
    int stidx = azero/9;
    int shfted = azero%9;
    int ls = stidx;
    ll temp;
    int carry = 0;
    for (int i=0; i<x.n; ++i, ++ls) {
        temp = (ll)e10[shfted] * x.c[i] + carry;
        result.c[ls] = temp%BASE;
        carry = temp/BASE;
    }
    result.c[ls] = carry;
    result.n = ls + (carry>0);
}

void appendzero(int azero, int d, BGM& cnt) {
    memset(cnt.c, 0, sizeof(cnt.c));
    int zg9 = azero/9;
    int wh = azero%9;
    ll td = d;
    while (wh) {
        td = td * 10LL;
        wh--;
    }
    int lef = td%BASE;
    int ri = td/BASE;
    cnt.c[zg9] = lef;
    cnt.c[zg9+1] = ri;
    cnt.n = zg9+1 + (ri>0);
}

void square(BGM& x, int _ud, BGM& xsqed, BGM& result, int rl) {
    int xc = x.c[x.n-1];
    int nod = rl - (x.n-1)*9;
    int d=_ud;/*
    while (xc) {
        nod++;
        xc/=10;
    }*/
    int rnm1 = (x.n-1)*9 + nod;
    int rn2m2 = 2*rnm1;
    BGM d2n2m2;
    appendzero(rn2m2, d*d, d2n2m2);
    
    BGM mid;
    BGM midr;
    singledigitmul(x, 2*d, mid);
    appendzeroX2(rnm1, mid, midr);
    
    memset(result.c, 0, sizeof(result.c));
    add(d2n2m2, midr, mid);
    add(mid, xsqed, result);
    /*
    printf("rl=%d, result.n=%d\n", rl, result.n);
    printf("x=");printBGM(x);
    printf("x^2=");printBGM(result);
    putchar('\n');*/
}

void runloop(int seed) {
    res[seed-5][0] = seed+'0';
    BGM x; memset(x.c, 0, sizeof(x.c));
    x.c[0] = seed; x.n = 1;
    
    int xsqi=0; memset(xsq[0].c, 0, sizeof(xsq[0].c)); memset(xsq[1].c, 0, sizeof(xsq[1].c));
    xsq[0].c[0] = seed*seed;
    xsq[0].n = 1;
    
    for (int i=2, zd; i<=500; ++i) {
        
        zd = -1;
        for (int d=0; d<=9; ++d) {
            int dign = i;
            int msb = (xsq[xsqi].c[(dign-1)/9]%e10[(dign%9)?(dign%9):9])/e10[(dign%9+8)%9];
            int oth = (2*d*(x.c[0]%10))%10;
            /*if (i<=10) {
                printf("i=%d, msb=%d, oth=%d, d=%d, dign=%d\n", i, msb, oth, d, dign);
                printf("x^2=");printBGM(xsq[xsqi]);
                printf("x=");printBGM(x);
            }*/
            if ((oth + msb)%10 == d) {
                res[seed-5][i-1] = d + '0';
                zd = d;
                break;
            }
        }
        
        if (zd != -1) {
            square(x, zd, xsq[xsqi], xsq[xsqi^1], i-1);
            xsqi ^= 1;
            x.c[(i-1)/9] += zd*e10[(i-1)%9];
            x.n = (i-1)/9+1;
        } else {
            printf("WARN: check seed=%d in n=%d\n", seed, i);
            return;
        }
    }
}

void work() {
    runloop(5);
    runloop(6);
    
    char lastcmp = 0;
    for (int i=0; i<500; ++i) {
        if (res[0][i] < res[1][i]) {
            pos[i] = 0;
        } else if (res[0][i] > res[1][i]) {
            pos[i] = 1;
        } else {
            pos[i] = lastcmp;
        }
        lastcmp = pos[i];
    }
}

int test() {
    int bignum_a[] = {10291, 29929302, 199292939, 29392};
    int bignum_b[] = {30309, 199291, 288818007};
    int bignum_scc[] = {94, 904958488, 585885849, 589300392, 930923094};
    int bignum_xc[] = {9006, 951145720, 210190612, 301593508, 891666098, 585053647, 672333965, 298723502, 942532836};
    
    BGM a, b, sqc, pc;
    initbgm(a, 4, bignum_a);
    initbgm(b, 3, bignum_b);
    initbgm(pc, 5, bignum_scc);
    initbgm(sqc, 9, bignum_xc);
    
    printf("a:");printBGM(a);
    printf("b:");printBGM(b);
    
    BGM c;
    add(a, b, c);
    printf("c=a+b=");printBGM(c);
    
    singledigitmul(a, 1000, c);
    printf("a*1000=");printBGM(c);
    
    appendzeroX2(20, b, c);
    printf("appendzeroX2, b<<10^20=");printBGM(c);
    
    appendzero(20, 999999999, c);
    printf("appendzero, 999999999<<10^20=");printBGM(c);
    
    //square(pc, 7, sqc, c);
    //printf("5pc^2=");printBGM(c);
    /*
    BGM _0625, _0625sq2;
    _0625.c[0] = 625;
    _0625.n = 1;
    _0625sq2.c[0] = 390635;
    _0625
    square()

    
    */
}

void printg(int fi) {
    
}

int main() {
    work();
    
    int t, N, c=1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        printf("Case #%d:", c++);
        if (N == 1) {
            printf(" 0 1 5 6\n");
        } else {            
            int fi = pos[N-1];
            if (res[fi][N-1] == '0' && res[fi^1][N-1] == '0') {
                printf(" Impossible");
            }
            
            if (res[fi][N-1] > '0') {
                putchar(' ');
                for (int i=N-1; i>=0; --i) {
                    putchar(res[fi][i]);
                }
            }
            
            if (res[fi^1][N-1] > '0') {
                putchar(' ');
                for (int i=N-1; i>=0; --i) {
                    putchar(res[fi^1][i]);
                }
            }
            putchar('\n');
        }
    }
}
