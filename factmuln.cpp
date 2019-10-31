#include <stdio.h>

int prime[10000];
char flag[32000];

int _max(int a, int b) {
	return a>b?a:b;
}

int buildPrimes() {
	int p = 1;
	
	prime[0] = 2;
	
	int i;
	for (i=3; i*i <= 32000; i+=2) {
		if (!flag[i]) {
			prime[p++] = i;
			
			for(int j=i*i; j <= 32000; j += 2*i) {
				flag[j] = 1;
			}
		}
	}
	
	for (; i <= 32000; i+=2) {
		if (!flag[i]) {
			prime[p++] = i;
		}
	}
	
	return p;
}

// pN = number to factor, primesN = numberofprimes
int factorize(int pN, int *pa, int *exp, int primesN) {
	
	int N = pN;
	int pp = 0;
	int pe = 0;
	
	while (pp < primesN && N >= prime[pp]) {
		if (N % prime[pp] == 0) {
			
			N /= prime[pp];
			pa[pe] = prime[pp];
			exp[pe] = 1;
			
			while (N % prime[pp] == 0) {
				N /= prime[pp];
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
	int T, N;
	
	int primesN = buildPrimes();
	
	int psa[16];
	int pexp[16];
	
	scanf("%d", &T);
	while(T--) {
		scanf("%d",&N);
		
		if (N == 1) {
			printf("1\n");
			continue;
		}
		
		int pp = factorize(N, psa, pexp, primesN);
		
		int max = -1;
		for (int i=0, pe, ps; i<pp; ++i) {
			
			pe = pexp[i];
			ps = 0;
			
			for (int j=psa[i], s; ; ++j) {
				if (j%psa[i] == 0) {
					
					int ji = j;
					s = 0;
					while (ji % psa[i] == 0) {
						ji /= psa[i];
						++s;
					}
					
					ps += s;
					
				}
				
				if (pe > ps) {
					pe -= ps;
				} else {
					max = _max(max, j);
					break;
				}
				
			}
		}
		
		printf("%d\n", max);
	}
	return 0;
}
