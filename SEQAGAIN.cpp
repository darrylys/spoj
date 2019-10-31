#include<stdio.h>

#define MOD1 1000000007
#define PHMOD 1000000006
#define ll long long

typedef struct {
    int m[2][2];
} Mat;

Mat getid() {
    Mat id;
    id.m[0][0] = id.m[1][1] = 1;
    id.m[0][1] = id.m[1][0] = 0;
    return id;
}

Mat getbase(int k) {
    Mat b;
    b.m[0][0] = b.m[1][0] = k; 
    b.m[0][1] = 1;
    b.m[1][1] = 0;
    return b;
}

Mat mul(Mat& a, Mat& b, int mod) {
    Mat c;
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2; ++j) {
            c.m[i][j] = 0;
            for (int k=0; k<2; ++k) {
                c.m[i][j] = (int)(((ll)c.m[i][j] + ((ll)a.m[i][k] * b.m[k][j])%mod)%mod);
            }
        }
    }
    return c;
}

Mat mexp(ll exp, int mod, Mat& ID, Mat& base) {
    if (exp==0) {
        return ID;
    }
    if (exp==1) {
        return base;
    }
    
    Mat half = mexp(exp>>1, mod, ID, base);
    if (exp&1LL) {
        Mat half2 = mul(half, half, mod);
        return mul(half2, base, mod);
    } else {
        return mul(half, half, mod);
    }
}

int bigmod(int base, int exp, int mod) {
    if (exp==0) return 1;
    if (exp==1) return base;
    int half = bigmod(base, exp>>1, mod);
    if (exp&1) {
        return (int)((((ll)half * half)%mod * (ll)base)%mod);
    } else {
        return (int)(((ll)half * half)%mod );
    }
}

int main() {
    int t, f0, f1, k;
    ll n;
    Mat ID = getid();
    
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %lld %d", &f0, &f1, &n, &k);
        if (n==0) { printf("%d\n", f0); } 
        else if (n==1) printf("%d\n", f1);
        else {
            if (k==0) {
                printf("1\n");
            } else {
                Mat base = getbase(k);
                Mat resk = mexp(n-1, PHMOD, ID, base);
                int f0kmod = resk.m[1][0];
                int f1kmod = resk.m[0][0];
                
                int f0r = bigmod(f0, f0kmod, MOD1);
                int f1r = bigmod(f1, f1kmod, MOD1);
                
                printf("%d\n", (int)(((ll)f0r*f1r)%MOD1));
            }
        }
    }
    
    return 0;
}
