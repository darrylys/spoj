/*
AC 0.05s 2.7M SPOJ

algo: math
simple observation shows that the all of the numbers other than the largest will have
equal numbers of its positives and negatives.

a1 +- a2 +- a3 +- a4 +- ... +- an

for all subset s e S of (a1, ..., an), find the sum of F(s)
if all F(s) is expanded to its terms:
F(s) = a1 - a2 + a3 ...

all terms but a1 will be zeros because the number of (am) is the same as (-am) ( 2 <= m <= n )
so they cancel each other out.

The sum of all F(s) is therefore:
max(A) * 2^(N-1)

Time: O(lg(N))
Space: O(lg(N))

PS: 
I tried to solve this problem with python first but it throws NZEC for some reason.
Tried to use re (RegEx) package but still NZEC.
So, fuck it, use CPP.
*/

#include <stdio.h>

typedef long long ll;
const ll MOD = 1000000007;

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
	int N;
	ll amax = 0;
	ll ai;

	scanf("%d", &N);
	scanf("%lld", &ai);
	amax = ai;

	for (int i=1; i<N; ++i) {
		scanf("%lld", &ai);
		if (ai > amax) {
			amax = ai;
		}
	}

	if (amax < 0) {
		ll k = -amax / MOD;
		amax += (k+1)*MOD;
	}

	amax %= MOD;

	printf("%lld\n", (amax * bigmod(2, N-1, MOD))%MOD);
}
