#include <stdio.h>
#include <time.h>
#include <math.h>

#define ll long long
#define MAXN 100000000

char flag[MAXN / 8 + 1];
int prime[6000000];
int mul[6000000];

int buildPrime(int M) {
	
	int p = 0;
	prime[p] = 2;
	mul[p] = 2;
	p++;
	int i;
	
	for (i=3; i*i <= MAXN; i+=2) {
		
		if (!(flag[i>>3] & (1<<(i&7)))) {
			
			prime[p] = i;
			mul[p] = ((ll)i * mul[p-1])%M;
			p++;
			
			for (int j = i*i; j <= MAXN; j+= 2*i) {
				flag[j>>3] |= (1<<(j&7));
			}
		}
		
	}
	
	for ( ; i <= MAXN; i+=2) {
		if (!(flag[i>>3] & (1<<(i&7)))) {
			prime[p] = i;
			mul[p] = ((ll)i * mul[p-1])%M;
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

ll expman(int xp, int d) {
	ll x = xp;
	if (d == 1) return x;
	if (d == 2) return x*x;
	if (d == 3) return x*x*x;
	if (d == 4) return x*x*x*x;
	return -1;
}

int findmanroot(int searchlim, int X, int d) {
	int u=1, v=searchlim, c;
	
	while (1) {
		if (u >= v) {
			return u-1;
		} else {
			c = (u+v)/2;
			ll cx = expman(c, d);
			//printf("c=%d, cx=%lld\n", c, cx);
			
			if (X < cx) {
				v = c;
			} else if (X > cx) {
				u = c+1;
			} else {
				return c;
			}
		}
	}
}

int getexp(int base, int X) {
	ll m = base;
	int e = 0;
	while (m <= X) {
		e++;
		m *= base;
	}
	return e;
}

int main(void) {
    //clock_t tStart = clock();

	int T, M, N;
	scanf("%d %d", &T, &M);
	int nprimes = buildPrime(M);
	int np[4];
	
	while (T--) {
		scanf("%d", &N);
		
		ll snv = 1;
		int lastp = 1;
		for (int i=0; prime[i] * prime[i] * prime[i] * prime[i] <= N; ++i) {
			
			//this one gives WA. probably precision problem again.
			//int exp = (int) floor(log(N) / log(prime[i]));
			
			//this one gives AC
			int exp = getexp(prime[i], N);
			
			ll forn = bigmod(prime[i], exp, M);
			snv *= forn;
			snv %= M;
			lastp = prime[i];
		}
		
		np[0] = N;
		
		// pow(N, 1/3.) gives wrong answer for several cases. So, manual approach it is!
		np[1] = findmanroot(N, N, 2);
		np[2] = findmanroot(np[1]+1, N, 3);
		np[3] = lastp;
		
		for (int i=0, bn; i<3; ++i) {
			bn = binsearch(np[i], prime, nprimes);
			
			if (bn >= 0) { 
				snv *= mul[bn];
				snv %= M;
			}
		}
		
		int bx = binsearch(np[3], prime, nprimes);
		int np3m3 = 1;
		
		if (bx >= 0) {
			np3m3 = bigmod(mul[bx], M-4, M);
		}
		
		snv *= np3m3;
		snv %= M;
		
		printf("%d\n", (int)snv);
		
	}
    return 0;
}
