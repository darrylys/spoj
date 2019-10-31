/*
AC 0.00s 2.7M SPOJ

algo: math
E(N): number of password with even number of zeros
O(N): number of password with odd number of zeros

obviously:
E(N) + O(N) = 10^N ----------------------------------------------------- (1)

E(N) = C(N,0)*9^N + C(N,2)*9^(N-2) + C(N,4)*9^(N-4) + ...
O(N) = C(N,1)*9^(N-1) + C(N,3)*9^(N-3) + C(N,5)*9^(N-5) + ...

it can be shown that:
O(N) = E(N-1) + 9*O(N-1) ----------------------------------------------- (2)

combining (1) and (2), we get:
O(N) = 9*O(N-1) + E(N-1)
     = 9*O(N-1) + 10^(N-1) - O(N-1)
	 = 8*O(N-1) + 10^(N-1)

unroll O(N) and the pattern can be found. It is a geometric sum
with a0 = 10^(N-1) and r = 8/10

thus, the formula is:
O(N) = 10^(N-1) * (1 - (8/10)^N) / (1-(8/10))
     = 10^N * ((10^N - 8^N) / 10^N) / 2
     = (10^N - 8^N) / 2

E(N) = 10^N - O(N)
     = (10^N + 8^N)/2

Time: O(T*lg(N))
Space: O(lg(N))

*/

#include <stdio.h>

typedef long long ll;
const int MOD = 314159;
const int INV2 = 157080;

ll bigmod(int base, int exp, int mod) {
	if (exp == 0 || base == 1) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	half = (half*half)%mod;
	if (exp&1) {
		half = (half*base)%mod;
	}
	return half;
}

int main() {
	int T, N;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &N);
		
		ll e10 = bigmod(10, N, MOD);
		ll e8 = bigmod(8, N, MOD);
		printf("%lld\n", ((e10 + e8) * INV2)%MOD);

	}
}