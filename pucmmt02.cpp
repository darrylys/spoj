/*
AC 0.28s 6.4M SPOJ

algo:
math

to handle whether a*b is square free, find the gcd.
if gcd(a,b) > 1, then it is NOT a square free number
	let a = g * k where g = gcd(a,b)
	let b = g * l
	a * b = g^2 * k * l which contains g^2 which is a square number.

now, A and B is handled separately. If both are square free, then a*b is a square free. else, no
to check a number N is a square free, 
check all primes from 1 to N^(1/3) whether N can be divided by p^2. If it is, then it is not square free.
continue checking until N is completely factorized.

If there exist remains, or none of the primes from 1 to N^(1/3) divides N,
then N might be:
	1) a prime
	2) p1 * p2 where p1 and p2 > N^(1/3)
	3) p^2.

case 1) and 2) are both square free numbers so our concern is only at case 3).
just check whether the remains of N is a square.

classic C way, x = sqrt(N) and find out whether x*x == N.
to handle imprecision of floating point, as usual, check ranges of x.
while (x*(x++) < N);
and finally, check if x*x == N. If yes, the N is a square number, else, N is a square free number.

Note, c sqrt is actually quite precise ~ 10^18. I'm surprised!
the number of adjustment iterations are mostly 0 if N is perfect square and 1 otherwise.

Time complexity: O(N^(1/3))
Space complexity: O(N^(1/3))

*/

#include <cstdio>
#include <cmath>
#include <assert.h>

#define ll long long
#define MAXN 10000000
#define MAXP 670000
//#define DEBUG

char flag[MAXN / 8 + 1];
int prime[MAXP];

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a%b);
}

int buildPrime() {
	int p = 0;
	prime[p] = 2;
	p++;
	int i;
	
	for (i=3; i*i <= MAXN; i+=2) {
		if (!(flag[i>>3] & (1<<(i&7)))) {
			prime[p] = i;
			p++;
			for (int j = i*i; j <= MAXN; j+= 2*i) {
				flag[j>>3] |= (1<<(j&7));
			}
		}
	}
	
	for ( ; i <= MAXN; i+=2) {
		if (!(flag[i>>3] & (1<<(i&7)))) {
			prime[p] = i;
			p++;
		}
	}
	
	return p;
}

bool isSquareFree(int nprimes, ll x) {
	
	bool sqn = true;
	for (int i=0; i<nprimes && x>1; ++i) {
		
		if (x % prime[i] == 0) {
			x /= prime[i];
		}
		
		if (x % prime[i] == 0) {
			return false;
		}
		
		ll p = prime[i];
		ll p3 = p*p*p;
		
		assert (p3 > 0);
		
		if (p3 > x) { // afraid of overflow!
			break;
		}
		
	}
	
	if (x == 1) {
		return true;
	}
	
	ll ss = (ll)floor(sqrt(x));
	ll s = ss;
	
	while (s*s < x) {
		s+=1;
	}
	
	//printf("s*s=%lld, x=%lld, diff=%d\n", s*s, x, s-ss);
	
	sqn = s*s != x;
	
	return sqn;
	
}

int main() {
	
	int nprime = buildPrime();
	
	int T; ll A, B;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld", &A, &B);
		ll r = gcd(A, B);
		if (r > 1) {
			printf("NO\n");
			
		} else {
			if (isSquareFree(nprime, A) && isSquareFree(nprime, B)) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
			
		}
		
	}
	
}

