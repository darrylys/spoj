#include<stdio.h>

#define ll long long
#define MAXN 100000000
//#define DEBUG

char flag[MAXN / 8 + 1];
int prime[6000000];

int buildPrime() {
	int p = 0;
	prime[p] = 2;
	p++;
	int i;
	
	for (i=3; i*i <= MAXN; i+=2) {
		if (!(flag[i>>3] & (1<<(i&7)))) {
			prime[p] = i;
			p++;
			for (int j = i*i; j <= MAXN; j+= 2*i) {
				flag[j>>3] |= (1<<(j&7));
			}
		}
	}
	
	for ( ; i <= MAXN; i+=2) {
		if (!(flag[i>>3] & (1<<(i&7)))) {
			prime[p] = i;
			p++;
		}
	}
	
	return p;
}

ll bigmod(int base, int exp, int mod) {
	if (exp == 0) return 1;
	else if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	if (exp&1) {
		return (((half*half)%mod) * base)%mod;
	} else {
		return (half*half)%mod;
	}
}

int binsearch(int x, int *arr, int N) {
	int u=0, v=N, c;
	while(1) {
		if (u>=v) {
			return u-1;
		} else {
			c = (u+v)/2;
			if (x < arr[c]) {
				v = c;
			} else if (x > arr[c]) {
				u = c+1;
			} else {
				return c;
			}
		}
	}
}

int main() {
	int noOfPrimes = buildPrime();
	
	int T, N, M;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &M);
		
		int lastPrime = 1;
		ll divcnt = 1;
		
		#ifdef DEBUG
		printf("list of primes: \n");
		for (int i=0; prime[i] <= N; ++i) {
			printf("%d\t", i);
		}
		printf("\n");
		for (int i=0; prime[i] <= N; ++i) {
			printf("%d\t", prime[i]);
		}
		printf("\n");
		#endif
		
		#ifdef DEBUG
		printf("loop to sqrt(%d):\n", N);
		#endif
		
		for (int i=0; prime[i]*prime[i] <= N; ++i) {
			int e = 0;
			ll p = prime[i];
			
			#ifdef DEBUG
			printf("prime\t%d", p);
			#endif
			
			while (p <= N) {
				e += N/p;
				p *= prime[i];
			}
			
			#ifdef DEBUG
			printf(" exp\t%d\n", e);
			#endif
			
			divcnt *= (e+1);
			divcnt %= M;
			
			lastPrime = prime[i];
		}
		
		#ifdef DEBUG
		printf("lastPrime=%d\n", lastPrime);
		
		printf("second half: \n");
		#endif
		
		int Nl = binsearch(N, prime, noOfPrimes)+1;
		
		#ifdef DEBUG
		printf("BEGIN: Nl=%d\n", Nl);
		#endif
		
		int idx;
		int lim;
		for (int i=1; i*i < N; ++i) {
			lim = N/(i+1);
			idx = binsearch(lim, prime, Nl);
			
			int noz = Nl - idx - 1;
			ll t = bigmod(i+1, noz, M);
			divcnt *= t;
			divcnt %= M;
			
			#ifdef DEBUG
			printf("bigmod(%d,%d,%d)=%lld\n", i+1, noz, M, t);
			printf("binsearch(%d): idx=%d\n", lim, idx);
			printf("Nl=%d, noz=%d\n", Nl, noz);
			#endif
			
			Nl = idx+1;
			
			#ifdef DEBUG
			printf("lastPrime=%d, prime[%d]=%d\n", lastPrime, Nl-1, prime[Nl-1]);
			#endif
			
			if (prime[Nl-1] == lastPrime) break;
		}
		
		#ifdef DEBUG
		printf("divcnt=");
		#endif
		printf("%lld\n", divcnt);
	}
	
}
