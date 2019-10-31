#include<stdio.h>

#define DIM 9
#define MOD 1000000007
#define ll long long

//#define DEBUG

int primefl[22] = {0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0};

typedef struct {
    int m[DIM][DIM];
} Mat;

Mat mbuf[50];

void printmr(Mat& a) {
    for (int i=0; i<DIM; ++i) {
        for (int j=0; j<DIM; ++j) {
            printf("%d ", a.m[i][j]);
        }
        putchar('\n');
    }
}

Mat getID() {
    Mat id;
    for (int i=0; i<DIM; ++i) {
        for (int j=0; j<DIM; ++j) {
            id.m[i][j] = i==j;
        }
    }
    return id;
}

Mat getBase() {
    Mat b;
    
    for (int i=1; i<=DIM; ++i) {
        for (int j=1; j<=DIM; ++j) {
            b.m[i-1][j-1] = primefl[i+j];
        }
    }
    
    return b;
}

Mat mul(Mat& a, Mat& b, int mod) {
    Mat c;
    for (int i=0; i<DIM; ++i) {
        for (int j=0; j<DIM; ++j) {
            c.m[i][j] = 0;
            for (int k=0; k<DIM; ++k) {
                c.m[i][j] = (int)(((ll)c.m[i][j] + ((ll)a.m[i][k] * b.m[k][j])%mod)%mod);
            }
        }
    }
    return c;
}

Mat add(Mat& a, Mat& b, int mod) {
    Mat c;
    for (int i=0; i<DIM; ++i) {
        for (int j=0; j<DIM; ++j) {
            c.m[i][j] = ( a.m[i][j] + b.m[i][j] )%mod;
        }
    }
    return c;
}

Mat msxp(Mat& base, int exp, int mod, int rc, Mat& ID) {
    if (exp == 0) {
        mbuf[rc] = base;
        return ID;
    }
    if (exp == 1) {
        mbuf[rc] = mul(base, base, mod);
        return add(ID, base, mod);
    }
    
    if (exp&1) {
        Mat half = msxp(base, exp>>1, mod, rc+1, ID);
        mbuf[rc] = mul(mbuf[rc+1], mbuf[rc+1], mod);
        Mat arex = add(mbuf[rc+1], ID, mod);
        return mul(half, arex, mod);
    } else {
        Mat half = msxp(base, (exp>>1)-1, mod, rc+1, ID);
        Mat t = mul(mbuf[rc+1], mbuf[rc+1], mod);
        mbuf[rc] = mul(t, base, mod);
        Mat tadd = add(half, mbuf[rc+1], mod);
        Mat t2a = mul(mbuf[rc+1], tadd, mod);
        return add(half, t2a, mod);
    }
}

int main() {
    Mat ID = getID();
    Mat base = getBase();
    
    int vm[DIM];
    for (int i=0; i<DIM; ++i) {
        vm[i] = 0;
        for (int j=0; j<DIM; ++j) {
            vm[i] += base.m[j][i];
        }
    }
    
    #ifdef DEBUG
    {
        printf("ID+Base\n");
        Mat ipm = add(ID, base, MOD);
        printmr(ipm);
        printf("===========\n");
        
        printf("base*(ID+Base)\n");
        Mat ixipm = mul(base, ipm, MOD);
        printmr(ixipm);
        printf("===========\n");
        
        printf("ID+base*(ID+base)\n");
        Mat ipixipm = add(ID, ixipm, MOD);
        printmr(ipixipm);
        printf("===========\n");
        
        ll sum = 4;
        for (int i=0; i<DIM; ++i) {
            for (int j=0; j<DIM; ++j) {
                sum = sum + (ll)vm[j] * ipixipm.m[j][i];
            }
        }
        printf("%lld\n", sum%MOD);
    }
    #endif
    
    int t, n, c=1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (n==1) printf("4\n");
        else {
            //printf("processing=%d in line %d\n", n, c++);
            Mat res = msxp(base, n-2, MOD, 0, ID);
            ll sum = 4;
            
            for (int i=0; i<DIM; ++i) {
                for (int j=0; j<DIM; ++j) {
                    sum = sum + (ll)vm[j] * res.m[j][i];
                }
            }
            printf("%lld\n", sum%MOD);
        }
    }
    return 0;
}
