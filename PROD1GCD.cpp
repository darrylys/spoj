/*
AC 0.28s 16M SPOJ

Some commenters pointed out Memoization but I don't use that.
I don't even know what algorithm is that.

Algo:
Math, find patterns. No need for complex math formula for this.
Not even Euler Totient function. Plain old finding patterns.

Use excel and calculate all gcd in MxN matrix

Now, notice the pattern in row N
notice this pattern:
GCD(N, 1), GCD(N, 2), ..., GCD(N, M)

Then, take close attention to the pattern of the following:
GCD(p, 1), GCD(p, 2), ..., GCD(p, M) for p is prime.

the pattern would be:
1, 1, 1, ..., p, 1, 1, 1 ..., p, 1, 1, ..., p,  and so on...

Now, notice the pattern of:
GCD(p1*p2, 1), GCD(p1*p2, 2), ..., GCD(p1*p2, M) for p1 and p2 is prime and p1 != p2

It can be seen that the pattern is actually an overlap of two patterns:
GCD(p1, M) and GCD(p2, M).

and when M = lcm(p1, p2), the GCD is lcm(p1, p2).

So, if all of those GCD is multiplied, the product is:
p1 ^ (floor(M/p1)) * p2 ^ (floor(M/p2))
This will automatically include the lcm part.

for GCD(p1^k, M) pattern, the product is:
p1 ^ (floor(M/p1) + floor(M/(p1^2)) + floor(M/(p1^3)) + ...)

Combining the two, the product of GCD(N, 1) ... GCD(N, M) would be:
if N = p1^e1 * p2^e2 * ... * pn^en
p1 ^ (floor(M/p1) + floor(M/(p1^2)) + ... + floor(M/(p1^e1))) * 
p2 ^ (floor(M/p2) + floor(M/(p2^2)) + ... + floor(M/(p2^e2))) *
....
pn ^ (floor(M/pn) + floor(M/(pn^2)) + ... + floor(M/(pn^en)))

Since we have to calculate all n from 1 to N, we can use above formula and multiply all n.
This is very similar to factorizing a factorial. factoring N!.
If each prime is grouped together, the result will be like:
p ^ (k1 * floor(M/p) + k2 * floor (M/p^2) + ... )
with k1 is the number of terms of p ^ floor(M/p)
and k2 is the number of terms of p ^ floor (M/p^2)

How many of these are available if we have to multiply 1, 2, ..., N which is N! ?
This is easily achieved by remembering how to factor a factorial. 
It has been used to find the number of zeros in a factorial, for instance.
To find the number of zeros, find the exponent of 5 if N! is factored.
using the following formula:
floor(N/5) + floor(N/25) + floor(N/125) + ...

This turns out to be our solution.
The number of terms will be:
k1 = floor(N/p1)
k2 = floor(N/p1^2)
...
km = floor(N/p1^m)

let S <- min(M,N)
Time: O( T*(sqrt(S)*lg(S) + (S/ln(S)))*lg(M*N) )
Space: O(10^7)

*/

#include <stdio.h>

//#define CALCTIME

#ifdef CALCTIME
#include <time.h>
#endif

typedef long long ll;

const int MAXN = 10000005;
const int MAXP = 1000000;
const int MOD = 1000000007;

char flag[MAXN];
int primes[MAXP];

//#define DEBUG

int buildPrimes() {
	
	int np = 1;

	flag[2] = 1;
	primes[0] = 2;

	int i;
	for (i=3; i*i < MAXN; i+=2) {
		if (!flag[i]) {
			primes[np++] = i;
			flag[i] = 1;

			int d = i<<1;
			for (int j=i*i; j < MAXN; j += d) {
				flag[j] = 1;
			}
		}
	}

	for (; i<MAXN; i+=2) {
		if (!flag[i]) {
			primes[np++] = i;
		}
	}

	return np;
}

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

// not used
int factor(int N, int* fn, int* fe) {
	
	int nfac = 0;
	if ((N&1) == 0) {
		int e = 0;
		fn[nfac] = 2;
		do {
			e++;
			N>>=1;
		} while ((N&1) == 0);
		nfac++;
	}

	while (N > 1) {
		
		int fac = flag[N];
		if (N%fac == 0) {
			int e = 0;
			fn[nfac] = fac;
			do {
				e++;
				N /= fac;
			} while (N%fac == 0);
			fe[nfac] = e;
			nfac++;
		}
	}

	if ( N > 1 ) {
		fn[nfac] = N;
		fe[nfac] = 1;
		nfac++;
	}

	return nfac;
}

// not used.
ll calcnsum(int p, int N, int maxe) {
	
	ll pdiv = p;
	ll sum = 0;

	for (int i=0, ndp; i<maxe; ++i) {
		ndp = N/pdiv;

		sum += pdiv * ndp * (ndp-1) / 2 + (N % pdiv) * ndp;

		pdiv *= p;
	}

	return sum;
}

int main() {
#ifdef CALCTIME
	clock_t tStart = clock();
#endif

	int np = buildPrimes();
	int T, iN, iM, N, M;
	ll mul;

#ifdef DEBUG
	printf("np=%d\n", np);
#endif

	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &iN, &iM);
	
		if (iN > iM) {
			M = iN; N = iM;
		} else {
			M = iM; N = iN;
		}

		mul = 1;

		for (int n=0, p; n<np && primes[n] <= N; ++n) {
			p = primes[n];

			ll exp = 0;

			for (ll i=p; i<=N; i*=p) {
				exp += (N/i)*(M/i);
			}

#ifdef DEBUG
			if (n == 0) {
				printf("exp=%lld\n", exp);
			}
#endif

			exp %= MOD-1;
			mul *= bigmod(p, (int)exp, MOD);
			mul %= MOD;
		}

		printf("%lld\n", mul);
	}

#ifdef CALCTIME
	fprintf(stderr, "Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
#endif
	return 0;
}
