#include <stdio.h>

#define ll long long
#define MAXP 32000
#define MAXN (1000000000)

bool flag[MAXP];
int primes[MAXP];
int fac[50];
int exp[50];

int buildPrimes() {
	
	int p=1;
	primes[0] = 2;
	
	for (int i=3; i < MAXP; i+=2) {
		if (!flag[i]) {
			primes[p++]=i;
			
			int d=i<<1;
			for (int j=i*i; j<MAXP; j+=d) {
				flag[j] = true;
			}
		}
	}
	return p;
}

int factor(int N, int nprime) {
	
	int fi = 0;
	for (int i=0; i<nprime && primes[i]*primes[i] <= N; ++i) {
		
		if (N % primes[i] == 0) {
			fac[fi] = primes[i];
			exp[fi] = 0;
			
			do {
				exp[fi]++;
				N /= primes[i];
			} while (N % primes[i] == 0);
			
			fi++;
		}
		
	}
	
	if (N > 1) {
		fac[fi] = N;
		exp[fi] = 1;
		fi++;
	}
	
	return fi;
}

int _phi_lim(int A, int startFactor, int nfactors, int sign, int div) {
	if (startFactor == nfactors) {
		return sign * (A / div);
	}
	
	// skip this number
	int sum = _phi_lim(A, startFactor+1, nfactors, sign, div);
	sum += _phi_lim(A, startFactor+1, nfactors, -sign, div*fac[startFactor]);
	
	return sum;
}

// seems working
int phi_lim(int A, int nfactors) {
	return _phi_lim(A, 0, nfactors, 1, 1);
}

int phi_N(int N, int nfactors) {
	int topN = 1;
	int mupN = 1;
	for (int i=0; i<nfactors; ++i) {
		topN *= fac[i]-1;
		mupN *= fac[i];
	}
	int phiN = N / mupN * topN;
	return phiN;
}

ll find(ll X, int nfactors, int N, int phiN) {
	
	ll left = X / N * phiN;
	ll right = phi_lim((int)(X%N), nfactors);
	
	return left + right;
}

int main() {
	int nprimes = buildPrimes();
	
	int T, c=1;
	scanf("%d", &T);
	
	ll A, B; int N;
	while (T--) {
		scanf("%lld %lld %d", &A, &B, &N);
		
		int nf = factor(N, nprimes);
		//for (int i=0; i<nf; ++i) {
		//	printf("%d^%d ", fac[i], exp[i]);
		//}
		//printf("\n");
		
		//printf("phi_lim(%d)=%d\n", A, phi_lim(A, nf));
		
		int phiN = phi_N(N, nf);
		ll sa = find(A-1, nf, N, phiN);
		ll sb = find(B, nf, N, phiN);
		
		printf("Case #%d: %lld\n", c++, sb-sa);
		
	}
	
	return 0;
}

