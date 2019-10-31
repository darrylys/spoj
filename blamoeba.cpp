#include<stdio.h>

/*
AC 0.47s 2.7M SPOJ

algo:
math

after a bit of analyzing, one can see that the problem asks:
M^N * X mod Y == 0; yeah...

however, there are some constraints:
M^k X > Y for 1 <= k < N
M^N X == Y

so, it is not the mod form that is being asked.

lets say
day 1. MX - Y
day 2. M(MX - Y) - Y
day 3. M(M(MX-Y)-Y)-Y
and so on...

one can see that if MX < Y in any of the step, it will go on negative and can never come back!
thus, if we set:

N_______________________
M(M(..(MX-Y)-Y)-Y)...)-Y == 0

MX > Y is automatically enforced!
if MX == Y at the beginning, the next day will be 0!

so, the formula is:
M^N X - Y(1 + M + M^2 + ... + M^(N-1)) == 0
M^N X - Y(M^N-1)/(M-1) == 0

 X      (M^N - 1) / (M - 1)
--- ==  -------------------
 Y              M^N

of course, smallest X and Y is achieved when gcd(X,Y) = 1
from here on, we can use induction to prove that gcd(X,Y) is always 1 for any N

base case:
N = 1
X = (M-1)/(M-1) = 1
Y = M
gcd(X,Y) = 1

inductive case:
assume:
gcd((M^N - 1) / (M - 1), M^N) = 1

set for N <- N+1
gcd((M^(N+1) - 1) / (M - 1), M^(N+1)) = ?
gcd(M((M^N - 1) / (M-1))+1, M * M^N)

let
X = (M^N - 1) / (M-1)
Y = M^N

the above turns to:
gcd(MX+1, MY)
gcd(MX, MY) = M since gcd(X,Y)=1
so, gcd(MX+1, MY) must be 1.

therefore:
for any N, gcd(X,Y) = 1

calculate:
X = (M^N - 1) / (M - 1) MOD 10^9+7
Y = M^N mod 10^9+7

done.

time complexity: O(T (lg N + lg MOD))
space complexity: O(1)

*/

#define MOD (1000000007)
#define ll long long
//#define _DEBUG

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

inline ll invmod(ll base) {
	return bigmod(base, MOD-2, MOD);
}

int main() {
	int T, M, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &M, &N);
		
		ll X = (((bigmod(M, N, MOD) + MOD - 1)%MOD) * invmod(M-1))%MOD;
		ll Y = bigmod(M, N, MOD);
		
		printf("%lld %lld\n", X, Y);
		
	}
}
