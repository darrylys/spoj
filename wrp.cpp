
/*
algo:

find the coeff of x^N in expansion of (x+x^2+...+x^M)^K
(x+x^2+...+x^M)^K 
	= (x^K)(1+x+x^2+...+x^(M-1))^K
	= (x^K)((1-x^M)/(1-x))^K
	= (x^K)
		[(1 - C(K,1)x^M + C(K,2)x^2M - C(K,3)x^3M ... {binomial expansion here... } +- C(K,K)x^KM)] (expansion of (1-x^M)^K) -> A
		[C(K-1,K-1) + C(K,K-1)x + C(K+1,K-1)x^2 + ...] (expansion of (1/(1-x))^K from generating function)					 -> B
	= so, all ya hav to do is to multiply A and B and find coeff of X^(N-K).
	= solvable in O((N-K)/M)
	
	C(K,X) -> C(K,X+1)
	K! / (X! (K-X)!  --> K! (K-X)/ (X!(X+1) (K-X)!  -->  C(K,X) * (K-X) / (X+1)
	
	C(X,K) -> C(X+1,K)
	x! / (x! k!) --> (x)! (x+1) / (k! (x-k)!(x-k+1)) --> C(x,k) * (x+1) / (x-k+1)
*/

#include <stdio.h>

#define MOD (1000000007)
#define MAXN (100005)
#define ll long long

int invmod[MAXN];
int BCoef[MAXN];

ll bigmod(int b, ll e, int mod) {
	if (e == 0 || b == 1) return 1;
	if (e == 1) return b % mod;
	
	ll mid = bigmod(b, e>>1L, mod);
	ll mid2 = ((ll) mid * mid) % mod;
	if (e&1) {
		return ((mid2 * b) % mod);
	}
	
	return (mid2);
}

void buildInvMod() {
	for (int i=1; i<MAXN; ++i) {
		invmod[i] = (int)bigmod(i, MOD-2, MOD);
	}
}

/*
C(K,X) -> C(K,X+1)
	K! / (X! (K-X)!  --> K! (K-X)/ (X!(X+1) (K-X)!  -->  C(K,X) * (K-X) / (X+1)
*/
ll getNextCBinom(ll val, int K, int X) {
	// val * (K-X) / (X+1)
	return (((val * (K-X))%MOD) * invmod[X+1])%MOD;
}

/*
C(Z,K) -> C(Z+1,K)
	z! / (z! k!) --> (z)! (z+1) / (k! (z-k)!(z-k+1)) --> C(z,k) * (z+1) / (z-k+1)
*/
ll getNextCGenF(ll val, int Z, int K) {
	return (((val * (Z+1))%MOD) * invmod[Z-K+1])%MOD;
}

ll solve(int N, int K, int M) {
	//printf("N=%d, K=%d, M=%d\nBCoef: 1", N, K, M);
	
	BCoef[0] = 1;
	for (int i=1; i<=(N-K); ++i) {
		BCoef[i] = getNextCGenF(BCoef[i-1] , K-1+i-1 , K-1);
		//printf(" %d", BCoef[i]);
	}
	
	ll sum = 0;
	ll coef = 1;
	int sgn = 1;
	//printf("\nCOEF: 1");
	for (int i=0; (N-K-i) >= 0; i+=M) {
		sum = sum + (((sgn * coef + MOD)%MOD) * BCoef[N-K-i])%MOD;
		sum %= MOD;
		coef = getNextCBinom(coef, K, i/M);
		sgn = -sgn;
		//printf(" %lld", coef);
	}
	
	//printf("\n");
	return sum;
	
}


int main() {
	buildInvMod();
	
	int T, N, K, M;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &N, &K, &M);
		printf("%lld\n", solve(N,K,M));
	}
	
	return 0;
}

