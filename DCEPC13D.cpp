#include <stdio.h>

#define ll long long
#define BIG (1000000000)

int primes[] = {2  ,  3  ,  5  ,  7  ,  11  ,  13  ,  17  ,  19  ,  23  ,  29  ,  31  ,  37  ,  41  ,  43  ,  47, -1};

ll _C[50][50];

void buildC() {
	for (int i=0; i<50; ++i) {
		_C[i][0] = _C[i][i] = 1;
		for (int j=1; j<i; ++j) {
			_C[i][j] = _C[i-1][j] + _C[i-1][j-1];
		}
	}
}

ll C(int N, int M) {
	if (N < M) return 0;
	return _C[N][M];
}

int bigmod(int base, int exp, int mod) {
	if (exp == 0) return 1;
	if (exp == 1) return base % mod;
	
	int half = bigmod(base, exp>>1, mod);
	
	if (exp&1) {
		return (half * half * base) % mod;
	} else {
		return (half * half) % mod;
	}
}

// seems good
int LUC(int N, int R, int p) {
	
	ll ret = 1;
	
	while (N > 0) {
		
		int tn = N%p;
		int tr = R%p;
		
		ret *= (C(tn, tr) % p);
		
		if (ret >= BIG) ret %= p;
		
		N /= p;
		R /= p;
	}
	
	return ret % p;
	
}

// find C(N, R) mod M
int CRT(int N, int R, int M) {
	
	ll sum = 0;
	for (int i=0; M >= primes[i] && primes[i] > 0; ++i) {
		
		if (M % primes[i] == 0) {
			
			// get a1 from x == a1 mod p1
			// so, calculate C(N,R) mod p1
			ll a1 = LUC(N, R, primes[i]);
			
//			printf("primes[i]=%d, a1=%lld\n", primes[i], a1);
			
			if (a1) {
//				printf("M / primes[i] = %d\n", (M / primes[i]));
//				printf("bigmod(%d,%d,%d) = %d\n", (M / primes[i]) % primes[i], primes[i]-2, primes[i], bigmod((M / primes[i]) % primes[i], primes[i]-2, primes[i]));
				
				sum += a1 * (M / primes[i]) * bigmod((M / primes[i]) % primes[i], primes[i]-2, primes[i]);
				
				if (sum >= M) {
					sum %= M;
				}
			}
			
		}
	}
	
	return (int)(sum % M);
	
}

int main() {
	buildC();
	
//	printf("%lld\n", C(20, 6));
	//printf("%lld\n", C(49, 24));
	
	int T, N, R, M;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&N,&R,&M);
		
		
		
		//printf("%d\n", LUC(N,R,M));
		
		printf("%d\n", CRT(N,R,M));
	}
	return 0;
}
