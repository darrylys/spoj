/*
AC 0.35s 2.7M SPOJ

algo:
we need to calculate:

let:
[] = floor function

sum:
[A/B] + [2A/B] + [3A/B] + ...  + [NA/B]

if A >= B:
A = kB + r

= [(kB+r)/B] + [2(kB+r)/B] + ... + [N(kB+r)/B]
= [r/B] + [2r/B] + [3r/B] + ... + [Nr/B] + k * (1 + 2 + ... + N)

the case is then reduced to A < B

how to solve A<B case?

we can view this geometrically. 
the idea is to mirror the Y = Ax/B line against Y=X axis.

now, we can see that the number of grid points in lower triangle when A < B case
is simply the total grid points in a rectangle - the number of grid points in lower triangle in A > B case (Y = Bx / A line).

@see book1.xslx for images

these facts allow for log(N) algorithm like euclid GCD

source:
http://www.hsin.hr/coci/archive/2009_2010/contest1_solutions.zip
extract and find solutions.pdf

*/

#include <stdio.h>

#define ll long long

ll gcd(ll a, ll b) {
	return b ? gcd(b, a%b) : a;
}

ll F(ll n, ll a, ll b) {
	
	if (a < b) {
		ll g = gcd(a, b);
		return n * (n*a / b) - F((n*a/b), b, a) + (n / (b / g));
	}
	if (a%b == 0) {
		return a / b * n * (n+1) / 2 ;
	}
	return a / b * n * (n+1) / 2 + F(n, a%b, b);
}

int main() {
	int T;
	ll N, A, B;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld %lld", &N, &A, &B);
		printf("%lld\n", N+1 + F(N, A, B));
	}
}
