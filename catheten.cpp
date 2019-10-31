#include <stdio.h>

#define ll long long
//#define DEBUG

int primeArray[20000];
char flag[32002];

int buildPrimes() {
	
	int s = 0;
	primeArray[s++] = 2;
	
	int di;
	
	int i;
	for (i=3; (ll)i*i <= 32000; i+=2) {
		if (!flag[i]) {
			primeArray[s++] = i;
			
			di = i<<1;
			for (int j=i*i; j <= 32000; j+= di) {
				flag[j] = 1;
			}
		}
	}
	
	for (; i<=32000; i+=2) {
		if (!flag[i]) {
			primeArray[s++] = i;
		}
	}
	
	return s;
}

ll F(int *primes, int *exp, int n) {
	ll pcalc[2][n+1];
	ll sum = 1;
	ll allmul = 1;
	
	for (int i=0; i<n; ++i) {
		sum *= (exp[i]+1);
	}
	
	#ifdef DEBUG
	printf("n=%d\n", n);
	printf("sum[0]\t%lld\n", sum);
	#endif
	
	allmul = sum;
	
	// for pz = 1
	pcalc[1][n]=0;
	for (int i=n-1; i>=0; --i) {
		pcalc[1][i] = pcalc[1][i+1] + exp[i] * allmul / (exp[i]+1);
	}
	
	sum += pcalc[1][0];
	
	#ifdef DEBUG
	printf("sum[1]\t%lld\t", sum);
	for (int i=0; i<=n-1; ++i) {
		printf("%lld\t", pcalc[1][i]);
	}
	putchar('\n');
	#endif
	
	
	// next cases
	for (int pz = 2, bpz; pz <= n; ++pz) {
		bpz = pz&1;
		
		pcalc[bpz][n-pz+1] = 0;
		
		for (int i=n-pz; i>=0; --i) {
			pcalc[bpz][i] = pcalc[bpz][i+1] + exp[i] * (pcalc[bpz^1][i+1]) / (exp[i]+1);
		}
		
		sum += pcalc[bpz][0];
		
		#ifdef DEBUG
		printf("sum[%d]\t%lld\t", pz, sum);
		for (int i=0; i<=n-pz; ++i) {
			printf("%lld\t", pcalc[bpz][i]);
		}
		putchar('\n');
		#endif
	}
	
	
	
	return (sum-1)>>1;
}

int factorize(int pN, int *pa, int *exp, int primesN) {
	
	int N = pN;
	int pp = 0;
	int pe = 0;
	
	while (pp < primesN && N >= primeArray[pp]) {
		if (N % primeArray[pp] == 0) {
			
			N /= primeArray[pp];
			pa[pe] = primeArray[pp];
			exp[pe] = 1;
			
			while (N % primeArray[pp] == 0) {
				N /= primeArray[pp];
				++exp[pe];
			}
			
			++pe;
		}
		
		++pp;
	}
	
	if (N > 1) {
		pa[pe] = N;
		exp[pe] = 1;
		pe++;
	}
	
	return pe;
}

int main() {
	int primesN = buildPrimes();
	
	int psa[16];
	int pexp[16];
	
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		
		#ifdef DEBUG
		printf("oldN=%d, N&1=%d\n", N, N&1);
		#endif
		
		if ((N&1) == 0) {
			N >>= 1;
		}
		
		#ifdef DEBUG
		printf("new N=%d\n", N);
		#endif
		
		int pp = factorize(N, psa, pexp, primesN);
		
		#ifdef DEBUG
		for (int i=0; i<pp; ++i) {
			printf("%d^%d ", psa[i], pexp[i]);
		}
		putchar('\n');
		#endif
		
		printf("%lld\n", F(psa, pexp, pp));
		
	}
	
	
}
