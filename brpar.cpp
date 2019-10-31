/*
AC 0.01s 2.7M SPOJ

algo: math
it may seem hard at first to look for the states for DP.
there are M bracket types with k1 brackets type 1, k2 brackets type 2, ..., km brackets type m.

However, there is actually no differences between brackets. Each brackets are interchangeable
No special relationship between any brackets, as such, they are interchangeable easily.
For example:
this sequence: ()[]{}
can be: []{}(), [](){}, {}()[], {}[](), (){}[]
basically, <><><> * permuting (){}[] around 3 slots = 1 * 3!/1!/1!/1! = 6
<><><> = sequence using 3 pair of brackets of format ()()(), ignoring bracket types.

So, the problem can be reduced to:
1. instead of m brackets, imagine there is only one bracket type and there are k1+k2+k3+...+km of those.
2. let F(N) is the number of valid bracket sequence using N bracket pairs. N = k1+k2+k3+...+km.
3. back to M brackets, the total number of bracket sequences using M brackets is F(N) * (the number to distribute M brackets in N pairs of slots)

the number to distribute M brackets in N pairs of slots
this is basic combinatorial problem:

the number = (k1+k2+...+km)! / (k1! * k2! * k3! * ... * km!)

to compute F(N):
F(N) can be constructed as follows:

[ N-1 ](0) --> the number of valid sequences using N-1 brackets, appended with (0) which is the valid sequence using 0 pairs of brackets, enclosed in a pair of bracket.
[ N-2 ](1) --> the number of valid sequences using N-2 brackets, appended with (1) which is the valid sequence using 1 pairs of brackets, enclosed in a pair of bracket.
[ N-3 ](2) --> the number of valid sequences using N-3 brackets, appended with (2) which is the valid sequence using 2 pairs of brackets, enclosed in a pair of bracket.
....
[ 0 ](N-1) --> the number of valid sequences using 0 brackets, appended with (N-1) which is the valid sequence using N-1 pairs of brackets, enclosed in a pair of bracket.

each of these are guaranteed to be distinct because the (x) part is different for each configuration if x is different

F(N) = \sigma i=0..(N-1) F(i)*F(N-1-i)
F(0) = 1

Combining the two is:
result = F(N) * (k1+k2+...+km)! / (k1! * k2! * k3! * ... * km!)

since F(N) is the same for any bracket configuration, it can be precomputed first.
N is maximum 1000 so N^2 algorithm is sufficient.

time complexity:
	O( precompute F + precompute factorial + processing time per testcase )
	O( N^2 + N + T * (M + lg(10^9+7)) )

space complexity:
	O( N )

*/

#include <stdio.h>

#define ll long long
#define MAXN (1001)
#define MOD (1000000007)

int fac[MAXN];
int F[MAXN];

ll bigmod(ll base, ll exp, int mod) {
	if (base == 0) {
		return exp == 0;
	}
    if (exp < 0) return 0;
    if (exp == 1) return base;
    if (exp == 0 || base == 1) return 1;
    
    ll half = bigmod(base, exp>>1, mod);
    ll half2 = (half*half)%mod;
    if (exp&1) {
        return (half2*base)%mod;
    }
    return half2;
}

int main() {
	fac[0]=1;
	for (int i=1; i<MAXN; ++i) {
		fac[i] = ((ll)fac[i-1]*i)%MOD;
	}
	
	F[0] = 1;
	for (int N=1; N<MAXN; ++N) {
		F[N] = 0;
		for (int i=0; i<N; ++i) {
			F[N] = (F[N] + (ll)F[i]*F[N-1-i])%MOD;
		}
	}
	
	int T, M, K;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &M);
		
		int totalN = 0;
		ll mulK = 1;
		
		for (int i=0; i<M; ++i) {
			scanf("%d", &K);
			mulK *= fac[K];
			mulK %= MOD;
			totalN += K;
		}
		
		ll comb = ((ll)fac[totalN] * bigmod(mulK, MOD-2, MOD))%MOD;
		
		ll res = (F[totalN] * comb)%MOD;
		
		printf("%lld\n", res);
	}
	
	return 0;
}
