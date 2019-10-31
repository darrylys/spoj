/*
algorithm: T*r^2*log(N)
*/

#include<stdio.h>

#define MOD (1000000007)
#define MAXC (450)
#define ll long long

int C[MAXC][MAXC];
ll F[MAXC];

ll bigmod(int base, int exp, int mod) {
	if (exp == 0) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	if (exp&1) {
		return (((half*half)%mod) * base) % mod;
	} else {
		return (half*half)%mod;
	}
}

void buildC() {
	for (int i=0; i<MAXC; ++i) {
		C[i][i] = C[i][0] = 1;
		for (int j=1; j<i; ++j) {
			C[i][j] = C[i-1][j] + C[i-1][j-1];
			if (C[i][j] >= MOD) {
				C[i][j] -= MOD;
			}
		}
	}
}

ll find(int N, int a, int R) {
	// f(N,r) = a/(a-1) (a^N * (N+1)^r - 1 - (\sigma x->[1..r] C[r][x] f(N, a, r-x)))
	// compute base case f(N, a, 0) = (a^(N+1)-1) / (a-1) - 1
	
	ll invam1 = bigmod(a-1, MOD-2, MOD);
	ll an = bigmod(a, N, MOD);
	ll n1r = 1;
	
	F[0] = ((( ((((an*a)%MOD) - 1 + MOD)%MOD) * invam1)%MOD) - 1 + MOD)%MOD;
	
	ll front = (a * invam1)%MOD;
	
	for (int r=1; r<=R; ++r) {
		n1r *= (N+1);
		n1r %= MOD;
		
		ll sum = 0;
		for (int x=1; x<=r; ++x) {
			sum += (C[r][x] * F[r-x])%MOD;
		}
		
		sum %= MOD;
		
		F[r] = (front * (((an * n1r)%MOD - 1 - sum + MOD)%MOD))%MOD;
		
	}
	
	return F[R];
	
}

int main() {
	buildC();
	
	int T, N, a, R;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &N, &a, &R);
		printf("%lld\n", find(N,a,R));
	}
}

