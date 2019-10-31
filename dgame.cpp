/*
AC, 0.00s, 2.6M, SPOJ

algo:
part a) obviously 2^N. calc 2^N mod M, M=1000000007
part b)
Use grundy number for analysis.

just manually enumerate the results via brute force program
the pattern emerged is very interesting
the idea is to count the number of losing positions reachable from the first move.

see book1.xslx for details

but the resulting pattern:
if N%4 == 3, no winning move possible. The current position is in losing position (grundy = 0)
if N%4 == 1, number of winning moves are (N+1)/2
else: #winning moves = N - 2^floor(lg(N)) + 1

*/

#include <stdio.h>

#define ll long long
#define MOD (1000000007)

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
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		
		ll a = bigmod(2, N, MOD);
		
		int b;
		if (N%4 == 3) b=0;
		else if (N%4 == 1) b=(N+1)/2;
		else {
			int k=1;
			
			while ( k < N ) {
				k<<=1;
			}
			
			if (k != N) k >>= 1;
			
			b=N-k+1;
		}
		
		printf("%lld %d\n", a, b);
	}
}
