#include<stdio.h>
#include<string.h>
#include<algorithm>

#define ull unsigned long long
#define MXST 36864

using namespace std;

              // 6 4 3 2  2  2  2  2  2  2  2  2
int prime[12] = {2,3,5,7,11,13,17,19,23,29,31,37};

// ordering matters...
int fac[42][12];
int gnfac[42];

ull accum[42][40000];
ull dp[42][40000];
ull glass[40000];

//idea: sort states.

bool comp(ull a, ull b) {
    return a>b;
}

int NUM(int* buf) {
    
    int ab7 = 0;
    
    ab7 = ab7*6+buf[0];
    ab7 = ab7*4+buf[1];
    ab7 = ab7*3+buf[2];
    
    for (int i=3; i<12; ++i){
        ab7 = (ab7<<1) + buf[i];
    }

    return ab7;
}

void TOARR(int code, int* buf) {
    for (int i=0; i<12; ++i) buf[i]=0;
    
    int lb = code&511;
    
    int c = 11;
    while (lb) {
        buf[c--] = lb&1;
        lb>>=1;
    }
    
    int hb = code>>9;
    
    buf[2] = hb%3;
    hb/=3;
    
    buf[1] = hb%4;
    hb/=4;
    
    buf[0] = hb%6;
    hb/=6;
    
}

void factorize(int n, int* buf) {
    
    buf[0] = 0;
    while (n%2 == 0) {
        buf[0]++;
        n/=2;
    }
    
    buf[1] = 0;
    while (n%3 == 0) {
        buf[1]++;
        n/=3;
    }
    
    buf[2] = 0;
    while (n%5 == 0) {
        buf[2]++;
        n/=5;
    }
    
    for (int i=3; i<12; ++i) {
        buf[i]=0;
        if (prime[i]==n) buf[i]=1;
    }
}

void gnfactorize(ull n, int* buf) {
    buf[0] = 0;
    while (n%2 == 0) {
        buf[0]++;
        n/=2;
    }
    
    buf[1] = 0;
    while (n%3 == 0) {
        buf[1]++;
        n/=3;
    }
    
    buf[2] = 0;
    while (n%5 == 0) {
        buf[2]++;
        n/=5;
    }
    
    for (int i=3; i<12; ++i) {
        buf[i]=0;
        //if (prime[i]==n) buf[i]=1;
        while (n%prime[i] == 0) {
            buf[i]++;
            n/=prime[i];
        }
    }
}

int max(int a, int b) {
    return (a>b)?a:b;
}

void vDP1() {
    
    int aState[12];
    int nwState[12];
    
    //n=1
    dp[1][0] = 1;
    
    for (int n=2; n<=40; ++n) {
        factorize(n, fac[n]);
        
        for (int s=0; s<MXST; ++s) {
            dp[n][s] = dp[n-1][s];
        }
        
        for (int s=0; s<MXST; ++s) {
            // compare n to the state
            TOARR(s, aState);
            int mul = 1;
            
            for (int i=0; i<12; ++i) {
                nwState[i] = max(fac[n][i], aState[i]);
            }
            
            int code = NUM(nwState);
            dp[n][code] = dp[n][code] + dp[n-1][s];
        }
    }
}

ull tonum(int* buf) {
    ull z = 1;
    int e;
    for (int i=0; i<12; ++i) {
        e = buf[i];
        while (e) {
            z *= prime[i];
            e--;
        }
    }
    return z;
}

void printdp() {
    int buf[12];
    for (int r=10; r<=10; ++r) {
        printf("R=%d\n", r);
        for (int j=0; j<MXST; ++j) {
            TOARR(j, buf); 
            for (int i=0; i<12; ++i) printf("%d ", buf[i]);
            printf(" tonum=%llu ::= %llu\n", tonum(buf), dp[r][j]);
        }
    }
}

void translate() {
    // do sort!
    
    int buf[15];
    
    for (int i=1; i<MXST; ++i) {
        TOARR(i, buf);
        glass[i] = tonum(buf);
    }
    
    //glass[0] = 0;
    sort(glass+1, glass+MXST, comp);
    
    for (int i=1; i<MXST; ++i) {
        //printf("i=%d 1. %llu\n", i, glass[i]);
        gnfactorize(glass[i], buf);
        //printf("i=%d 2. %llu\n\n", i, glass[i]);
        gnfac[i] = NUM(buf);
    }
    
    for (int i=1; i<=40; ++i) {
        accum[i][0] = 0;
        
        //printf("i=%d\n================\n", i);
        for (int j=1; j<MXST; ++j) {
            accum[i][j] = accum[i][j-1] + dp[i][gnfac[j]];
            //printf("[[ %d : glass[%d] = %llu ] : %llu]\n", j, j, glass[j], accum[i][j]);
        }
        //printf("\n");
    }
}

int main() {
    vDP1();
    translate();
    //printdp();
    
    int t, n, xc=1; 
    ull m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %llu", &n, &m);
        //printf("m=%llu\n", m);
        if (m==1) {
            printf("Case #%d: %llu\n", xc++, (((ull)1)<<n)-1);
        } else {
            
            int u=1,v=MXST,c, f;
            while (1) {
                
                c = (u+v)>>1;
                //printf("search c=%d glassc=%llu vs m=%llu\n", c, glass[c], m);
                
                if (u>=v) {
                    f = c-1;
                    break;
                }
                if (m > glass[c]) {
                    v = c;
                } else if (m < glass[c]) {
                    u = c+1;
                } else {
                    f = c;
                    break;
                }
            }
            //printf("f=%d\n", f);
            printf("Case #%d: %llu\n", xc++, accum[n][f]<<1);
        }
    }
    return 0;
}
