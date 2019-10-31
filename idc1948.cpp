/**
algo:

m = ceil(log(N))
10^m - N - 1 == N mod p
10^m - 2N - 1 == 0 mod p
so, just factor (10^m - 2N - 1), find the primes and find the correct smallest one.

little details when 10^m - 2N - 1 results in negative
X = 10^m - 2N

if X nonnegative, find X mod P == 1
else, find (-X) mod P == P-1

*/

#include <stdio.h>

#define MAXP (30000000)
#define MP (5500)

int primes[MP];
bool flag[MP];
int fac[11];
int e10[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

int buildPrime() {
	
	primes[0] = 2;
	int p=1;
	
	for (int i=3; i<MP; i+=2) {
		if (!flag[i]) {
			primes[p++] = i;
			
			for (int j=i*i, d=i<<1; j<MP; j+=d) {
				flag[j] = true;
			}
		}
	}
	
	return p;
}

int factor(int N, int nprime) {
	
	int f=0;
	for (int i=0; i<nprime && primes[i]*primes[i]<=N; ++i) {
		
		if (N%primes[i]==0) {
			fac[f++] = primes[i];
			
			do {
				N/=primes[i];
			} while (N%primes[i] == 0);
			
		}
		
	}
	
	if (N>1) {
		fac[f++] = N;
	}
	
	return f;
	
}

int main() {
	
	int nprime = buildPrime();
	
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		
		//printf("N=%d\n", N);
		
		int lim;
		for (int i=0; i<9; ++i) {
			if (N < e10[i]) {
				lim = e10[i];
				break;
			}
		}
		
		int x = lim - 2*N;
		int d = x - 1;
		if (d < 0) d = -d;
		
		if (d == 1) {
			printf("-1\n");
			continue;
		}
		
		int f = factor(d, nprime);
		
		if (x > 0) {
			for (int i=0; i<f; ++i) {
				if ((x) % fac[i] == 1) {
					printf("%d\n", fac[i]);
					break;
				}
			}
		} else {
			for (int i=0; i<f; ++i) {
				if ((-x) % fac[i] == (fac[i]-1)) {
					printf("%d\n", fac[i]);
					break;
				}
			}
		}
		
		
	}
	
}
