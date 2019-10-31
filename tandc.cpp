/*
AC 0.00s 2.8M SPOJ

algo: math

consider a sequence f(x) = x^k
now, the problem asks for g(x) = f(x+1) - f(x)
next, h(x) = g(x+1) - g(x)
and so on
until k times.

the act to find difference between two points in a graph is called differentiation
Basically, this operation performed k times to f(x) = x^k is the same as differentiating f(x) k times
The result:
f'k(x) = k!

the problem sets k = P^R - 1
which P = prime

After the sequence is differentiated k times, the list will only contain 1 number, k!
so, the value that we search is (P^R-1)!.

2 <= P <= 10^9
1 <= R <= 10^9

That's a lot.

Of course, it is impossible to actually calculate P^R-1, so, recall how to find the maximum K which P^K divides (P^R-1)!.

formula:
\sigma i=1..R floor(P^R-1 / P^i)

P^R / P^i = P^(R-i)
floor(P^R - 1 / P^i) = P^(R-i)-1.
since (P^(R-i)-1) * P^i = P^R - P.
and P^R - 1 - P^R + P = P-1 which is indivisible by P.

Therefore:
\sigma i=1..R floor(P^R-1 / P^i)
        = P^(R-1) -1 + P^(R-2)-1 + ... + P -1
		= P + P^2 + ... + P^(R-1) - (R-1)
		= (P (P^(R-1) - 1) / (P-1)) - (R-1) ------------------------ Sum of geometric series

Time: O(T * lg(R))
Space: O(lg(MOD))

*/

#include <stdio.h>

typedef long long ll;

const int MOD = 1000000007;

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
	int T, M, R;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &M, &R);
		//M * (M^(R-1) - 1) / (M-1) - (R-1) mod 10^9+7
		
		ll invm1 = bigmod(M-1, MOD-2, MOD);
		ll mxrm1 = bigmod(M, R-1, MOD);
		
		ll lef = (((M * (mxrm1 - 1 + MOD))%MOD) * invm1)%MOD;
		ll res = (lef - R + 1 + MOD)%MOD;
		
		printf("%lld\n", res);
		
	}
	return 0;
}