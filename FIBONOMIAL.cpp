/*
AC 0.08s 2.7M SPOJ

Algo: Matrix multiplication

f(n) = fibonacci
f(n) = f(n-1) + f(n-2)
f(0) = 0
f(1) = 1
D(n, x)    = x + x^2 + 2x^3 + 3x^4 + 5x^5 + 8x^6 + ... + f(n)  x^n
x D(n-1,x) =     x^2 +  x^3 + 2x^4 + 3x^5 + 5x^6 + ... + f(n-1)x^n (-)
----------------------------------------------------------------------
D(n,x) - x*D(n-1,x) = x + x^2 * D(n-2,x)
D(n,x) = x + x*D(n-1,x) + x^2 * D(n-2,x)

x = constant

the equation is simply:
                             / x   1  0 \
 < D(n-1,x), D(n-2,x), x > * | x^2 0  0 |
                             \ 1   0  1 /

with D(0,x) = 0, D(1,x) = x

Space: O(lg(N))
Time: O(T*lg(N))

*/

#include <stdio.h>
#include <string.h>

#define ll long long
#define MOD (1000000007)
#define N (3)
#define _DEBUG

inline int I(int r, int c) {
    return r*N + c;
}

const int BASE[] = {
    1, 0, 0, 
    0, 1, 0,
    0, 0, 1
};

void matmul(const int* ma, const int* mb, int* res) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            
            int c = I(i, j);
            ll tot = 0;
            
            for (int k=0; k<N; ++k) {
                tot += ((ll)ma[I(i, k)] * mb[I(k, j)])%MOD;
            }
            
            res[c] = tot % MOD;
        }
    }
}

void matexp(const int* a, ll exp, int* res) {
    
    if (exp == 0) {
        memcpy(res, BASE, sizeof(BASE));
        return;
    }
    
    if (exp == 1) {
        memcpy(res, a, N*N*sizeof(a[0]));
    }
    
    int tmp[9];
    matexp(a, exp>>1, tmp);
    
    int tmp2[9];
    matmul(tmp, tmp, tmp2);
    
    if (exp&1) {
        matmul(tmp2, a, res);
    } else {
        memcpy(res, tmp2, sizeof(tmp2));
    }
    
}

#ifdef _DEBUG
void printarr(int* a) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            printf("%d\t", a[I(i,j)]);
        }
        putchar('\n');
    }
}
#endif

int main() {
    int T;
    ll n, x;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld %lld", &n, &x);
        x %= MOD;
        
        if (n == 0) {
            printf("0\n");
            continue;
        }
        
        int res[9];
        int a[] = {
            (int)x          , 1, 0,
            (int)((x*x)%MOD), 0, 0,
            1               , 0, 1
        };
        
        matexp(a, n-1, res);
        
        printf("%lld\n", (x * (res[0] + res[6]))%MOD);
    }
    
    return 0;
}

