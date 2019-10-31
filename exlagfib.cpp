/*
1000000037 = 421×563×4219
now this is very interesting...

i'm confused how to calculate C(N,R) mod (that), can use lucas theorem + CRT for that
add with little generating function, quite solvable.

strange point for k >= 10^5. this is very odd!

formula used
\sigma (C(n,x) * b^(n-x) * c^x * X^(x(k-j))) X^(nj)
verified for fibonacci numbers, at least
*/

#include <stdio.h>

#define ll long long
#define MOD (1000000037)

int primes[] = {421, 563, 4219, -1};

int fac421[421];
int inv421[421];

int fac563[563];
int inv563[563];

int fac4219[4219];
int inv4219[4219];

int* facp[] = {fac421, fac563, fac4219};
int* invp[] = {inv421, inv563, inv4219};

ll bigmod(ll base, ll exp, int mod) {
    if (exp < 0) return 0;
    if (exp == 1) return base;
    if (exp == 0 || base == 1) return 1;
    
    ll half = bigmod(base, exp>>1, mod);
    ll half2 = (half*half)%mod;
    if (exp&1) {
        return (half2*base)%mod;
    }
    return half2;
}

void buildFac(int * x, int p) {
    x[0] = 1;
    for (int i=1; i<p; ++i) {
        x[i] = (x[i-1]*i)%p;
    }
}

void buildInv(int * x, int p) {
	x[0] = 0;
	for (int i=1; i<p; ++i) {
		x[i] = bigmod(i, p-2, p);
	}
}

// C(n,r) mod p
int CmodP(int n, int r, int p, int * fp, int * inv) {
    
    if (n < r) return 0;
    if (n == r) return 1;
    if (r == 1) return n;
    
    // (n!) / (r! * (n-r)!)
    int nf = fp[n];
    int rf = fp[r];
    int nmrf = fp[n-r];
    
    //return (int)(((ll)nf * bigmod(rf, p-2, p) * bigmod(nmrf, p-2, p))%p);
	return (int)(((ll)nf * inv[rf] * inv[nmrf])%p);
    
}

// seems good
int LUC(int N, int R, int p, int * fp, int * inv) {
	ll ret = 1;
	while (N > 0) {
		
		int tn = N%p;
		int tr = R%p;
		
		//ret *= (C(tn, tr) % p);
        ret = (ret * CmodP(tn, tr, p, fp, inv))%p; 
		
		N /= p;
		R /= p;
	}
	
	return ret % p;
	
}

// find C(N, R) mod M
int CRT(int N, int R, int M) {
	ll sum = 0;
	for (int i=0; M >= primes[i] && primes[i] > 0; ++i) {
		ll a1 = LUC(N, R, primes[i], facp[i], invp[i]);
		if (a1) {
			sum += a1 * (M / primes[i]) * bigmod((M / primes[i]) % primes[i], primes[i]-2, primes[i]);
			
			if (sum >= M) {
				sum %= M;
			}
		}
	}
	
	return (int)(sum % M);
}

ll find(int N, int J, int K, int B, int C) {
    if (N < K-1) {
        return 0;
    }
    if (N == K-1) {
        return 1;
    }
    
    ll sum = 0;
    if (J > (K-J)) {
        // pivot on J
        for (int n=0; (ll)n*J <= (N-K+1); n++) {
            int np = N-K+1-n*J;
            if ((np % (K-J)) == 0) {
                int x = np / (K-J);
				if (n >= x) {
					sum += (((ll)CRT(n, x, MOD) * bigmod(B, n-x, MOD))%MOD * (bigmod(C, x, MOD)))%MOD;
					sum %= MOD; 
				}
            }
        }
        
    } else {
        // pivot on K-J
        for (int x=0; (ll)x*(K-J) <= (N-K+1); x++) {
            int np = N-K+1-x*(K-J);
            if ((np % J) == 0) {
                int n = np / J;
				if (n >= x) {
					sum += (((ll)CRT(n, x, MOD) * bigmod(B, n-x, MOD))%MOD * (bigmod(C, x, MOD)))%MOD;
					sum %= MOD; 
				}
            }
        }
        
    }
    
    return sum;
}

int main( ) {
    buildFac(fac421, 421);
    buildFac(fac4219, 4219);
    buildFac(fac563, 563);
	
	buildInv(inv421, 421);
    buildInv(inv4219, 4219);
    buildInv(inv563, 563);
    
    int T, N, J, K, B, C;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d %d", &N, &J, &K, &B, &C);
        printf("%lld\n", find(N, J, K, B, C));
    }
}