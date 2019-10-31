#include <stdio.h>
//#include <ctime>

//using namespace std;

#define ll long long
#define MOD (1000000007)
#define MAXN (1000001)
//#define _DEBUG

int invexp[MAXN];
int primeflag[MAXN];
int primeexp[MAXN];
int factdiv[MAXN];
int factdivsum[MAXN+1];

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

void buildInvExp() {
	for (int i=1; i<MAXN; ++i) {
		invexp[i] = bigmod(i, MOD-2, MOD);
	}
}

void buildPrimes() {
	for (int i=3; i < MAXN; i += 2) {
		if (!primeflag[i]) {
			if ((ll)i*i <= (ll)MAXN) {
				for (int j=i*i; j < MAXN; j += 2*i) {
					primeflag[j] = i;
				}
			}
		}
	}
}

void build() {
	
	#ifdef _DEBUG
	printf("factdiv\n");
	#endif
	
	factdiv[0] = 1;
	
	for (int i=1; i<MAXN; ++i) {
		#ifdef _DEBUG
		printf("%d", i);
		#endif
		
		ll fprev = factdiv[i-1];
		
		factdiv[i] = 0;
		
		// factor i
		int x = i;
		int exp=0;
		while ((x&1) == 0) {
			x >>= 1;
			exp++;
		}
		
		#ifdef _DEBUG
		printf("\t%d^%d", 2, exp);
		#endif
		
		// 2^exp, fprev / (primeexp[2]+1) * (exp+1)
		fprev = (((fprev * invexp[primeexp[2]+1])%MOD) * (primeexp[2]+exp+1))%MOD;
		primeexp[2] += exp;
		
		while (x > 1) {
			
			int pdiv = primeflag[x];
			if (pdiv == 0) { // this is a prime number
				pdiv = x; // x is its only factor
			}
			
			exp = 0;
			while ((x%pdiv)==0) {
				x /= pdiv;
				exp++;
			}
			
			#ifdef _DEBUG
			printf("\t%d^%d", pdiv, exp);
			#endif
			
			fprev = (((fprev * invexp[primeexp[pdiv]+1])%MOD) * (primeexp[pdiv]+exp+1))%MOD;
			primeexp[pdiv] += exp;
			
		}
		
		factdiv[i] = (int)(fprev % MOD);
		
		#ifdef _DEBUG
		printf("\t%d\n", factdiv[i]);
		#endif
	}
	
	#ifdef _DEBUG
	printf("factdivsum\n");
	#endif
	
	factdivsum[0] = 0;
	for (int i=1; i<=MAXN; ++i) {
		factdivsum[i] = factdivsum[i-1] + factdiv[i-1];
		factdivsum[i] %= MOD;
		
		#ifdef _DEBUG
		printf("%d\t%d\n", i, factdivsum[i]);
		#endif
		
	}
}

int main() {
	
	//clock_t begin = clock();
	buildInvExp();
	//clock_t end = clock();
	//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//printf("invExp(): %lf\n", elapsed_secs);
	
	//begin = clock();
	buildPrimes();
	//end = clock();
	//elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//printf("buildprimes(): %lf\n", elapsed_secs);
	
	//begin = clock();
	build();
	//end = clock();
	//elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//printf("build(): %lf\n", elapsed_secs);
	
	#ifndef _DEBUG
	int T, L, R;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &L, &R);
		if (L > R) { printf("0\n"); continue; }
		
		printf("%d\n", (factdivsum[R+1] - factdivsum[L] + MOD)%MOD);
	}
	#endif
	return 0;
}
