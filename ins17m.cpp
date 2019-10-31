
/*
AC 6.66s 29M SPOJ C++ 4.3.2

Algo: Math
Concepts required:
    1. Fibonacci matrix exponentation
    2. Fast modular exponentation
    3. Number theory: Divisors, GCD, modulus division
    4. Simple integer factorization
    5. Prime sieve. Erathos sieve is enough
    6. GCD(fib(A), fib(B)) = fib(GCD(A, B))
    7. GCD(A^K, B^K) = GCD(A, B)^K
    8. Pisano periods
    9. Inclusion-exclusion principle

Q:
calc: \sigma 1 <= i < j <= N GCD(fib(A[i]^K, A[j]^K)) MOD (10^9+7)

the equation can be changed to:
      \sigma 1 <= i < j <= N fib(GCD(A[i], A[j])^K) MOD (10^9+7)

fibonacci under modulus is periodic. The period is called Pisano period.
Pisano period for fibonacci under mod 10^9+7 (1000000007) is 2*10^9+16 (2000000016)
      i.e. fib(i + 2000000016) = fib(i) MOD 10^9+7

Thus, the problem can be changed to:
      \sigma 1 <= i < j <= N fib( GCD(A[i], A[j])^K MOD (2000000016) ) MOD (1000000007)

It is hard to compute it directly. It is easier to handle if the equation is changed to:
           (1)                                                (2)
      0.5*((\sigma 1 <= i,j <= N fib( GCD(A[i], A[j])^K )) - (\sigma  1<=i<=N fib(A[i]^K) ))

equation (2) is easily computed in O(N * lg(K))

equation (1) can be solved with the observation that GCD(A[i], A[j]) must be a divisor to A[i].
So, instead of computing GCD(A[i], A[j]) one by one, it can be changed to:
      if gcd(A[i], A[j]) = x, how many fib(x^K) are there? K is constant by the way.
      and equation (1) can be rephrased as:
        \sigma 1 <= i <= N, d | A[i]  M(i) * fib(d^K)
        
      with M(i) is the number of elements in array that satisfies 
        GCD(A[i], A[j]) == d | 1 <= j <= N                               (3)
      
the divisors of A[i] can be enumerated from the prime factorization of A[i].
let A[i] = p1^e1 * p2^e2 * p3^e3 * ... * pn^en
let    d = p1^f1 * p2^f2 * ... * pm^fm
where m <= n and f1 <= e1

To find the number of elements in array such that GCD(A[i], A[j]) = d, 
A[j] format should be: d * w and gcd(w, A[i]) = 1
what is w?
      now, if d = p1^f1 * p2^f2 * ... * pm^em
        if f1 < e1, f2 < e2 ... fm < fn, m < n
            then w may not have p1, p2, ..., pm, ..., pn
            
        if f1 == e1, f2 < e2 ... fm < fn, m < n
            then w may not have p2, ..., pm, ..., pn but it MAY have p1 because A[j]
            would have p1^e1 as a factor and p1^(e1+x) would still have same gcd with A[i].
            
      w can be computed with inclusion-exclusion principle.

The algorithm above will time out if done just like that. I tried it and it requires 
17s for N=10^5, K=10^15 and random numbers.

To speed up, fibonacci result can be cached. Since K is constant, fibonacci result is only
determined by the gcd value. GCD value of array is limited in 1 to 10^6
With this caching, the time in my laptop is 2.5s. In SPOJ machine (faster than this laptop), 
this roughly is 1.5s.

Space: O(max(A) + N)
Time: O(N ln(N) + N * d(N) * ln(N) + maxA * lg(K)) | d(N) = number of divisors of N

largest d(N) for 1 <= N <= 10^6 is 240, when N = 720720
maximum number of distict prime factor is 7 when N = 510510

*/

#include <stdio.h>
#include <string.h>
//#include <Windows.h>

#define ll long long
//#define _DEBUG

#ifdef _DEBUG
#include <stdlib.h>
#include <time.h>
#endif

const int MOD = (1000000007);
const int PSNMOD = (2000000016);
const int N = (2);
const int N2 = N*N;
const int MAXA = 1000005;
const int MAXN = 100005;
const int MAXF = 8;

// the number of elements in A that is divisible by i
// 1 => #A that is divisible by 1
// 2 => #A that is divisible by 2
// etc.
int SA[MAXA];
int FA[MAXA];
int equ[MAXA];
int fibcache[MAXA];

// if flag[i] == false or flag[i] == i, i is prime
int flag[MAXA];

int A[MAXN];

typedef struct _FACTOR {
    int n;
    int p[MAXF];
    int e[MAXF];
} FACTOR;

FACTOR gfac[MAXN];

void buildPrimes() {
    flag[2] = 2;
    for (int i=3; i*i<MAXA; i+=2) {
        if (!flag[i]) {
            flag[i] = i;
            
            for (int j=i*i, d=2*i; j<MAXA; j+=d) {
                flag[j] = i;
            }
        }
    }
    
}

void factorize(int A, FACTOR& fac) {
    
    fac.n = 0;
    if (A%2 == 0) {
        
        fac.p[fac.n] = 2;
        fac.e[fac.n] = 0;
        
        do {
            A/=2;
            fac.e[fac.n]++;
        } while (A%2 == 0);
        
        fac.n++;
    }
    
    while (A > 1) {
        
        int prime = flag[A];
        if (prime == 0) {
            // A must be prime
            prime = A;
        }
        
        fac.p[fac.n] = prime;
        fac.e[fac.n] = 0;
        do {
            A /= prime;
            fac.e[fac.n]++;
        } while (A%prime == 0);
        fac.n++;
        
    }
    
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

const int MX_ID[] = {
    1, 0, 
    0, 1
};

const int MX_BASE[] = {
    1, 1,
    1, 0
};

const int MX_SIZE = sizeof(MX_BASE);

inline int I(int r, int c) {
    return r*N + c;
}

void matmul(const int* ma, const int* mb, int* res) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            ll tmp = 0;
            for (int k=0; k<N; ++k) {
                tmp += ((ll)ma[I(i, k)] * mb[I(k, j)])%MOD;
            }
            res[I(i, j)] = (int)(tmp%MOD);
        }
    }
}

void matexp(const int* a, ll exp, int* res) {
    
    if (exp == 0) {
        memcpy(res, MX_ID, MX_SIZE);
        return;
    }
    
    if (exp == 1) {
        memcpy(res, a, MX_SIZE);
        return;
    }
    
    int tmp[N2];
    matexp(a, exp>>1, tmp);
    
    if (exp&1) {
        int tmp2[N2];
        matmul(tmp, tmp, tmp2);
        matmul(tmp2, a, res);
    } else {
        matmul(tmp, tmp, res);
    }
}

ll bigmod(int base, ll exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base;
    
    ll half = bigmod(base, exp>>1, mod);
    if (exp&1) {
        return (((half*half)%mod)*base)%mod;
    } else {
        return (half*half)%mod;
    }
}

// fib[base^exp % mod]
// there are only limited number of possible bases (10^6)
// and the exp is constant K anyway.
// so we can cache the fibonacci results!
ll fib(int base, ll exp, int mod) {
    
    if (fibcache[base] != -1) {
        return fibcache[base];
    }
    
    ll x = bigmod(base, exp, mod);
    if (x == 0) {
        return fibcache[base] = 0;
    }
    
    if (x == 1) {
        return fibcache[base] = 1;
    }
    
    int fibmat[N2];
    matexp(MX_BASE, x-1, fibmat);
    
    return fibcache[base] = fibmat[0];
}

/**
tpn: length of array p.
upn: used prime index in array p
*/
int get_n_fibs(int tp, int upn, int *p, int tpn) {
    if (upn == tpn) {
        return SA[tp];
    }
    
    int sum = SA[tp];
    for (int i=upn; i<tpn; ++i) {
        int l = get_n_fibs(tp*p[i], i+1, p, tpn);
        sum -= l;
    }
    return sum;
}

ll enum_all_divs(int A, ll K, FACTOR &fac, int pi, int d, int *usf) {
    if (pi == fac.n) {
        int pf[MAXF];
        int nf = 0;
        for (int i=0; i<fac.n; ++i) {
            if (usf[i] < fac.e[i]) {
                pf[nf++] = fac.p[i];
            }
        }
        
        ll s = get_n_fibs(d, 0, pf, nf);
        return (s * fib(d, K, PSNMOD))%MOD;
    }
    
    ll sum = 0;
    int tp = 1;
    usf[pi] = 0;
    for (int i=0; i<=fac.e[pi]; ++i) {
        sum += enum_all_divs(A, K, fac, pi+1, d*tp, usf);
        tp *= fac.p[pi];
        usf[pi]++;
    }
    return sum%MOD;
}

int main() {
    memset(fibcache, -1, sizeof(fibcache));
    
    buildPrimes();
    
    int N;
    ll K;
    int maxA = -1;
    
    scanf("%d %lld", &N, &K);
    for (int i=0; i<N; ++i) {
        scanf("%d", &A[i]);
        if (A[i] > maxA) {
            maxA = A[i];
        }
        
        FA[A[i]]++;
    }
    
    SA[1] = N;
    for (int i=2; i<=maxA; ++i) {
        SA[i] = 0;
        for (int j=i; j<=maxA; j+=i) {
            SA[i] += FA[j];
        }
    }
    
    for (int i=0; i<N; ++i) {
        factorize(A[i], gfac[i]);
    }
    
    ll sum_fii = 0;
    for (int i=0; i<N; ++i) {
        sum_fii += fib(A[i], K, PSNMOD);
    }
    sum_fii %= MOD;
    
    ll sum_fij = 0;
    int usf[MAXF];
    for (int i=0; i<N; ++i) {
        if (!equ[A[i]]) {
            //memset(usf, 0, sizeof(usf));
            ll enumsum = enum_all_divs(A[i], K, gfac[i], 0, 1, usf);
            equ[A[i]] = (int)(enumsum%MOD);
        }
        sum_fij += equ[A[i]];
    }
    sum_fij %= MOD;
    
    printf("%lld\n", ((ll)(sum_fij - sum_fii + MOD) * 500000004)%MOD);
    
    return 0;
}
