/*
AC 0.00s 2.7M SPOJ

algo:
ad-hoc, math

after brute-forcing, the partition of N which product is maximum prefers
partitioning N to many small numbers.

it is preferable to partition N to many small numbers.
example: 11, 
	11 = 3 + 3 + 3 + 2, total product: 54
	11 = 5 + 6, total product: 30
	11 = 4 + 4 + 3, total product: 48

Unfortunatelly, I cannot prove this mathematically. This is obviously greedy algorithm
Maybe the proof can be rough-sketched by making a comparison between a^k and b^l
where a < b and a^k > b^l. how many b are required to make a^k < b^l while b*l <= N.
and show that it only works with b=3 and a=2. for b > 3, a<b wins all the way.

and partition 11 to add 1 to one of its terms is detrimental in any case.
Two smallest number possible that is bigger than 1 is 2 and 3.

In this case, the division prefers N to be divided to:
N = 3a + b
where a = floor(N / 3).

so, the product is:
3^(N/3)*2^x
where x is some number

when N mod 3 == 0 or 2, x = 1. 2 can just fill the gap easily
when N mod 3 == 1, the case becomes interesting!
change the N partition to 3*(N/3-1) + 4 instead of 3*(N/3)+1
because this partition (3*(N/3-1) + 4) will produce higher multiplication than 3*(N/3)+1 form.

time complexity: O(lg(N))
space complexity: O(lg(N))

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
	ll N;
	scanf("%lld", &N);
	
	if (N <= 3) {
		printf("%lld\n", N);
		return 0;
	}
	
	ll exp3 = N/3;
	int rem3 = N%3;
	int v2;
	
	if (rem3 == 1) {
		v2 = 4;
		exp3--;
		
	} else if (rem3 == 0) {
		v2 = 1;
		
	} else {
		v2 = 2;
		
	}
	
	printf("%lld\n", (bigmod(3, exp3, MOD) * v2)%MOD);
	
	return 0;
}
