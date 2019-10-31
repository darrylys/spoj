#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXP (100001)

int modfac[MAXP];
void buildModFac(int P) {
	modfac[0] = 1;
	for (int i=1; i<P; ++i) {
		modfac[i] = (int)(((ll)modfac[i-1]*i)%P);
	}
}

ll bigmod(int base, int exp, int mod) {
	if (exp == 0 || base == 1) return 1;
	if (exp == 1) return base%mod;
	
	ll half = bigmod(base, exp>>1, mod);
	if (exp&1) {
		return (((half*half)%mod) * base) % mod;
	} else {
		return (half*half)%mod;
	}
}

int spn(ll N, int P, int * buf) {
	ll xn = N;
	int i;
	for (i=0; xn; ++i) {
		buf[i] = (int)(xn%P);
		xn /= P;
	}
	return i;
}

ll C(int N, int R, int P) {
	if (N < R) return 0;
	if (R == 0 || N == R) return 1;
	if (R == 1) return N;
	
	return ((ll)modfac[N] * bigmod(modfac[R], P-2, P) * bigmod(modfac[N-R], P-2, P))%P;
}

int max(int a, int b) {
	return (a>b) ? a:b;
}

int main() {
	int T; ll N, K; int P;
	int NmodP[80], KmodP[80];
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld %d", &N, &K, &P);
		
		memset(NmodP, 0, sizeof(NmodP));
		memset(KmodP, 0, sizeof(KmodP));
		
		buildModFac(P);
		int nl = spn(N+1, P, NmodP);
		int kl = spn(K+1, P, KmodP);
		
		int mx = max(nl, kl);
		ll res = 1;
		for (int i=0; i<mx; ++i) {
			res *= C(NmodP[i], KmodP[i], P);
			res %= P;
		}
		
		printf("%lld\n", res);
	}
	return 0;
}

