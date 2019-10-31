/*
AC 0.06s 7.7M SPOJ

algo:
ad-hoc, simple number theory

Find the minimum X which has N odd number of divisors.
X is definitely not even because it has even number as several of divisors which are unneeded.

let:
X = p1^e1*p2^e2*...*pn^en 		; p is not 2
N = (e1+1)*(e2+1)*...*(en+1)

algo:
factor N
sort N from largest prime factor to smallest
N = p1^e1*p2^e2*...*pn^en
N = p1*p1*p1*...*p2*p2*...*pn*pn*...*pn

assign each prime factor of N to the primes from smallest to largest
for example: ....................................................................................(1)
N = 3^2 * 5^5 * 7*2
N = 7^2 * 5^5 * 3^2 ; arrange above factors

assign N factors:
A = 3^6 * 5^6 * 7^4 * 11^4 * 13^4 * 17^4 * 19^4 * 23^2 * 29^2
note that the number of divisors of A is exactly N.

now, from A, find the smaller number but keeping the prime factors exactly the same
Find smaller or equal to A with the number of divisor is N.

Note that N value is still 1024.

for example: ....................................................................................(2)
N = 1024 = 2^10
A0 = 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29 * 31
N = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2

try to modify N to:
N = 2^2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
with:
A1 = 3^3 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29
It can be seen that A1 < A0 because A1 = A0 * 3^2 / 31

now, if we try to modify N further to:
N = 2^3 * 2 * 2 * 2 * 2 * 2 * 2 * 2
we need:
A2 = 3^7 * 5 * 7 * 11 * 13 * 17 * 19 * 23
but, A2 > A1 because 3^4 > 29.

in this case, it is no longer possible to compress 3. Move to next prime which is 5.
try to modify N to:
N = 2^2 * 2^2 * 2 * 2 * 2 * 2 * 2 * 2
with:
A3 = 3^3 * 5^3 * 7 * 11 * 13 * 17 * 19 * 23
it can be seen that A3 < A1 because A3 = A1 * 5^2 / 29

If this process is continued, A3 is the smallest number obtainable when N = 1024.
A3 mod 1000000007 = 97947700

Note:
During the iteration, we need to check whether changing p1^x to p1^(x+1) and remove pn^en
we need to check whether p1^(x+1) < pn^en
In this case, x can be a large number (~10^7) if N is composed of two large primes or something.
So, obviously, long long is out of question. Compare them in log scale.
Compare them like: log(p1^(x+1)) < log(pn^en) === (x+1)*log(p1) < en*log(pn)
which is much easier to handle

That's pretty much the idea.

If N = p1^e1 * p2^e2
deal with each px^ex separately with the above iteration.
Whatever compression happened in px^ex does not influence any of other py^ey.

The rest, just use fast BigMod algorithm by squaring.
Sieve, just use standard Erathos Sieve.
if N is prime, the smallest number is 3^(N-1)

Time complexity: O(10^7 * ln(ln(10^7)) + T * sqrt(N))
Space complexity: O(10^7 * ln(ln(10^7)))

*/

#include <stdio.h>
#include <math.h>

#define ll long long
//#define _DEBUG

const int MXF = 10000000;
const int NNF = (MXF>>3)+1;
const int MOD = 1000000007;

char flag[NNF];
int prime[MXF/10];

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

int sieve() {
	int i, j, off;
	prime[0] = 2;
    int pntr=1;
	
	for (i=3;i*i <= MXF; i+=2) {
        if (!(flag[i>>3] & (1<<(i&7)))) {
            prime[pntr++] = i;
            off = i << 1;
            for (j=i*i; j <= MXF; j+=off) {
				flag[j>>3] |= (1<<(j&7));
			}
        }
    }
    for (;i<= MXF; i+=2) {
        if (!(flag[i>>3] & (1<<(i&7)))) {
			prime[pntr++] = i;
		}
    } 
	
	return pntr;
}

int compress(ll pfac, int exp, int spidx, int *pp, ll *pe) {
	
	for (int i=0; i<exp; ++i) {
		pp[i] = prime[spidx+i];
		pe[i] = pfac-1;
	}
	
	if (exp == 1) {
		return spidx+1;
	}
	
	for (int i=0; i<exp; ++i) {
		
		ll e = pe[i];
		
		while (i < exp-1) {
			
			// e^x -> e^(x+1)
			double ex = (pe[i]+1)*(e)*log(pp[i]);
			double far = pe[exp-1]*log(pp[exp-1]);
			
			#ifdef _DEBUG
			printf("ex=%lf, far=%lf\n", ex, far);
			#endif
			
			if (ex < far) {
				// remove far
				exp--;
				pe[i] = ((pe[i]+1)*(e+1)-1);
				
			} else {
				break;
			}
			
		}
	}
	
	return spidx+exp;
}

int main() {
	
	int nprimes = sieve();
	
	#ifdef _DEBUG
	printf("nprimes=%d\n", nprimes);
	
	for (int i=nprimes-1; i>=nprimes-10; --i) {
		printf("%d\n", prime[i]);
	}
	
	#endif
	
	ll N;
	ll fac[50];
	int exp[50];
	
	while (scanf("%lld", &N) != EOF) {
		
		#ifdef _DEBUG
		printf("\nINPUT(N=%lld)\n", N);
		#endif
		int nf = 0;
		
		for (int i=0; i < nprimes && N >= prime[i]*prime[i]; ++i) {
            if (N%prime[i] == 0) {
				
				exp[nf] = 0;
				fac[nf] = prime[i];
				
				do {
					N/=prime[i];
					exp[nf]++;
				} while (N%prime[i] == 0);
				
				nf++;
            }
        }
		
		if (N > 1) {
			exp[nf] = 1;
			fac[nf] = N;
			nf++;
		}
		
		#ifdef _DEBUG
		if (nf == 1 && exp[0] == 1) {
			printf("prime\n");
			
		} else {
			
			printf("factored:\n");
			for (int i=0; i<nf; ++i) {
				printf("%lld^%d ", fac[i], exp[i]);
			}
			printf("\n");
		}
		#endif
		
		// prime
		if (nf == 1 && exp[0] == 1) {
			printf("%lld\n", bigmod(3, N-1, MOD));
			continue;
		}
		
		int pp[50];
		ll pe[50];
		int nextPrime = 1;
		ll sol = 1;
		
		// assign largest primes to smallest ones first!
		for (int i=nf-1; i>=0; --i) {
			#ifdef _DEBUG
			printf("fac=%lld, exp=%d\n", fac[i], exp[i]);
			#endif
			
			int npt = compress(fac[i], exp[i], nextPrime, pp, pe);
			int nexp = npt - nextPrime;
			
			#ifdef _DEBUG
			printf("npt=%d, nexp=%d, nextPrime=%d\n", npt, nexp, nextPrime);
			printf("compressed\n");
			for (int i=0; i<nexp; ++i) {
				printf("%d^%lld ", pp[i], pe[i]);
			}
			printf("\n");
			#endif
			
			for (int i=0; i<nexp; ++i) {
				sol = (sol * bigmod(pp[i], pe[i], MOD))%MOD;
			}
			
			nextPrime = npt;
		}
		
		printf("%lld\n", sol);
	}
	
	return 0;
}



