/*
AC 0.00s 2.7M SPOJ
however, in prev time, got SIGESV error, probably stack overflow exception
this is fixed by adding if (N <= 0) in addition to L<=0.

algo:

let F(N) = the number of pairs (x, y), 0<=x,y<=N, which x^y == 2^z, z>=0

observe the following observations:
1. 
given set of numbers from 0 to 2^L-1,
let x is one of the numbers, it is always possible to find another number y inside that set
such that x^y = 2^z for 0 <= z < L

2. 
matching 2 numbers of format:
X   = 1xxxxxxxxxx
Y   = 0yyyyyyyyyy
X^Y = 10000000000
where x and y is {0, 1}

to make X^Y = 2^z, xxxxxxxxxx must be the same as yyyyyyyyyy to XOR of them all zeros.
so, X will be all possible numbers from 2^(L-1) to N while Y can always match X to make X^Y = 10000000000

the remaining possibility is:
X   = 1xxxxxxxxxx
Y   = 1yyyyyyyyyy
X^Y = 0??????????

which is basically the same as F(N - 2^(L-1)).
Recurse the function.

time complexity: O(lg(N))
space complexity: O(lg(N))

*/

#include <stdio.h>
#include <assert.h>

#define ll long long

const int MOD = 1000000007;

// L = number of bits in binary representation of N
ll F(ll N, int L) {
	
	if (N <= 0 || L <= 0) {
		return 0;
	}
	
	ll e2 = 1LL<<(L-1);
	
	ll a = (((e2>>1)%MOD)*(L-1))%MOD;
	ll b = (N - e2 + 1)%MOD;
	ll c = (a+b)%MOD;
	
	N -= e2;
	
	int lt=0;
	
	for (int i=L-1; i>=0; --i) {
		if (N >= (1LL << i)) {
			lt = i+1;
			break;
		}
	}
	
	return (c + F(N, lt))%MOD;
	
}

int main() {
	int T, L;
	ll N;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &N);
		
		for (int i=0; ; ++i) {
			if ((1LL<<i) <= N) {
				L = i+1;
			} else {
				break;
			}
		}
		
		printf("%lld\n", F(N, L));
	}
	
	return 0;
}
