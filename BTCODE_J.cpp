#include<stdio.h>

#define DIM 6
#define MOD 1000000007
#define ll long long

typedef struct {
    int m[DIM][DIM];
} Mat;

int max(int a, int b) {
    return (a>b)?a:b;
}

Mat getid() {
    Mat id;
    for (int i=0; i<DIM; ++i) {
        for (int j=0; j<DIM; ++j) {
            id.m[i][j] = i==j;
        }
    }
    return id;
}

void printmr(Mat& a) {
    for (int i=0; i<DIM; ++i) {
        for (int j=0; j<DIM; ++j) {
            printf("%d ", a.m[i][j]);
        }
        putchar('\n');
    }
}

Mat getbase(int k, int mod) {
    Mat b;
    
    b.m[0][0] = k-1;
    b.m[1][0] = max(k-2,0);
    b.m[2][0] = (k-1);
    b.m[3][0] = max(k-2,0);
    b.m[4][0] = (max(k-2,0)*2*(k-1) + (k-1));
    b.m[5][0] = ((k-1)*2 + max(k-2,0)*2*max(k-2,0) + max(k-2,0));
    
    b.m[0][1] = max(k-2,0)*(k-1);
    b.m[1][1] = (max((2*k-3),0) + max(k-3,0)*max(k-2,0));
    b.m[2][1] = max(k-2,0)*(k-1);
    b.m[3][1] = max(k-2,0)*max(k-2,0);
    b.m[4][1] = ((k-1)*2*(k-1) + max(k-2,0)*max(k-2,0)*2*(k-1) + max(k-2,0)*(k-1));
    b.m[5][1] = ((k-1)*2*max(k-2,0) + max(k-2,0)*(k-1)*2 + max(k-2,0)*2*max(k-2,0)*max(k-2,0) + max(2*k-3,0) + max(k-3,0)*max(k-2,0));
    
    b.m[0][2] = 0;
    b.m[1][2] = 0;
    b.m[2][2] = 0;
    b.m[3][2] = 0;
    b.m[4][2] = 2*(k-1);
    b.m[5][2] = 2*max(k-2,0);
    
    b.m[0][3] = 0;
    b.m[1][3] = 0;
    b.m[2][3] = (k-1);
    b.m[3][3] = max(k-2,0);
    b.m[4][3] = max(k-2,0)*2*(k-1);
    b.m[5][3] = ((k-1)*2 + max(k-2,0)*2*max(k-2,0));
    
    b.m[0][4] = 1;
    b.m[1][4] = 0;
    b.m[2][4] = 0;
    b.m[3][4] = 0;
    b.m[4][4] = 0;
    b.m[5][4] = 0;
    
    b.m[0][5] = 0;
    b.m[1][5] = 1;
    b.m[2][5] = 0;
    b.m[3][5] = 0;
    b.m[4][5] = 0;
    b.m[5][5] = 0;
    
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

Mat mexp(int exp, int mod, Mat& ID, Mat& base) {
    if (exp==0) {
        return ID;
    }
    if (exp==1) {
        return base;
    }
    
    Mat half = mexp(exp>>1, mod, ID, base);
    if (exp&1) {
        Mat half2 = mul(half, half, mod);
        return mul(half2, base, mod);
    } else {
        return mul(half, half, mod);
    }
}

int main() {
    int t, n, k;
    int arr[11];
    int rarr[6];
    Mat ID = getid();
    Mat base;
    Mat res;
    
    scanf ("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        if (n==1) printf("%d\n", k*k);
        else if (n==2) printf("%d\n", (ll)k * k * k * k % MOD);
        else {
            rarr[0] = (int)((3*k*(k-1)+k+(ll)k*(k-1)*max(k-2,0))%MOD);
            rarr[1] = (int)(((k-1)*2LL*k + (ll)max((2*k-3),0)*k*(k-1) + 
                (ll)max(k-2,0)*(k-1)*k + (ll)max(k-2,0)*2*k*(k-1) + 
                (ll)max(k-3,0)*k*(k-1)*max(k-2,0) + (ll)k*(k-1))%MOD);
                
            rarr[2] = 2*k;
            rarr[3] = 2*k*(k-1);
            rarr[4] = k;
            rarr[5] = k*(k-1);
            
            //printf("rarr=[");
            //for (int i=0; i<DIM; ++i) printf("%d ", rarr[i]);
            //printf("]\n");
            
            base = getbase(k, MOD);
            //printf("base\n");
            //printmr(base);
            res = mexp(n-2, MOD, ID, base);
            //printf("=================\n");
            
            //printf("result\n");
            //printmr(res);
            //printf("=================\n");
            
            arr[0] = arr[1] = 0;
            for (int i=0; i<2; ++i) {
                for (int j=0; j<DIM; ++j) {
                    arr[i] = (int)((arr[i] + (ll)rarr[j] * res.m[j][i])%MOD);
                }
            }
            
            //printf("arr[0]=%d + arr[1]=%d = %d\n", arr[0], arr[1], (arr[0] + arr[1])%MOD);
            printf("%d\n", (arr[0] + arr[1])%MOD);

        }
    }
    return 0;
}
