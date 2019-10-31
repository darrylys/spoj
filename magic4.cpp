/*
AC 0.10s 3.1M SPOJ

analysis of crazyb0y source:
isolate each function A,B,C,D,E,F to know what each function does
by running each function individually:

A is addition function
A(a,b) = a+b

B is kinda like modulo-wannabe operation which is reinforced by constant 1e9+7 in function D
in SPOJ, 1e9+7 is a very common constant to modulo the final result
B(a,b) = a>=b?a-b:a

run C and enumerate a and b manually.
the datatype (unsigned) is annoying so, during analysis, change the unsigned to int
and the pattern becomes much clearer.
C(a,b) = -(a%b)-1
~C(a,b) = a%b

D is multiplication function modulo 1e9+7
after replacing function A and C in D into their respective original forms

a ? ~C( ( A( D(a>>1, b)<<1, (a&1?b:0) ) ), 1e9+7) : 0; //original D
a ? ( (D(a>>1, b)<<1) + (a&1?b:0) ) % 1000000007 : 0; //~C and A are replaced

D(a,b)=(a*b)%1000000007

E is squaring function on modulo 1e9+7
E(a,b) = (a*a)%MOD

F is actually a fast exponential algorithm using exponentation by squaring
made into one liner. Nifty stuff
return b ? D( E ( F(a,b>>1) ), b&1?a:1 ) : 1;

Now, let's analysis the main function
for (k=2; k<=i; ++k) {
	if (C(i,k)*C(j,k)==1) { ............................. (1)
		break;
	}
}
if (k<=i) { ............................................. (2)
	continue;
}
r=D(r,F(i,j)); .......................................... (3)

C(a,b) = -(a%b)-1.
the only way to make C(a,b)*C(c,d)==1 is when both of them are -1
which means that a%b == 0.

so, C(i,k)*C(j,k)==1 means:
find where i%k == 0 and j%k == 0. k is divisor of both i and j

from the loop flow, it can be seen that (3) will not be executed
if k<=1 (2). (3) will be executed if k>i at point (2). To make this happen,
there should not be any k>=2 where k divides both i and j, which basically means that gcd(i,j)=1

So, the problem is to solve the following equation (** means exponentation):
     ___
     | | (a ** b) | for all ((1 <= a <= N), (1 <= b <= N), (gcd(a, b)=1))

Algo:
the equation can be rearranged to the following form in informal language:

a ** ( sum of integers from 1 to n where gcd (a, this) == 1 ) | (1 <= a <= N)

the sum of integers can be computed using inclusion / exclusion formula as usual
since the maximum number of different prime factors for N <= 10^5 is 7,
the maximum number of operations required to compute this is 128.

To do this, a method to factor all numbers from 2 to N is required (1 is ignored, 1^x is 1 anyway)
to quickly factor all numbers, first, use erathos sieve method to find the primes
but instead of using bit-flag as usual, the bit-flag is replaced with the largest prime that divides N
example:
flag[13] = 13
flag[8] = 2
flag[12] = 3
flag[30] = 5
flag[99] = 11
and so on... Actually, any prime would do (it doesn't have to be largest) but we choose the largest 
out of convenience.

Now, with this flag method, it is not required to search for primes that can divide N. Just consult
flag array and divide N with that!
the factorization of N can be easily done in lg(N) maximum.

The inclusion/exclusion part is solvable in maximum 128 operations.

The last part is the big-exp-mod algorithm which is lg(sumexp) where sumexp is the sum in inclusion/exclusion part
if required, Fermat little theorem can be used to reduce the number of operations to lg(min(1e9+6, sumexp)) 
which is not much actually.

These 3 operations are performed for each number 2 to N.

Time complexity: O(N * lg(N) * 128 * lg(1e9+6))
Space complexity: O(N + lg(N))

*/

#include <stdio.h>
//#include <ctime>
#define ll long long

//using namespace std;

const int MOD = (1000000007);
const int MODEXP = MOD-1;
const int MAXN = 100001;

int fp[MAXN];
ll E(ll a) { return (a*a)%MOD; }
ll F(ll a, ll b) { return b ? (E(F(a,b>>1))*(b&1?a:1))%MOD : 1; }

void flagprime() {
	int i;
	for (i=3; i*i<=MAXN; i+=2) {
		if (!fp[i]) {
			fp[i] = i;
			int d=i<<1;
			for (int j=i*i; j<MAXN; j+=d) {
				fp[j] = i;
			}
		}
	}
	for (;i<MAXN;i+=2){
		if (!fp[i]) {
			fp[i]=i;
		}
	}
}

int factor(int N, int * fac) {
	int p=0;
	if (!(N&1)) {
		fac[p++]=2;
		do {
			N>>=1;
		} while (!(N&1));
	}
	while (N>1) {
		int pfac=fp[N];
		fac[p++]=pfac;
		while(N%pfac==0){
			N/=pfac;
		}
	}
	return p;
}

int find(int N, int * fac, int nfac) {
	ll tl=0; int d, t, ti, n1;
	for (int i=0; i<(1<<nfac); ++i) {
		d=1; t=i; ti=0; n1=0;
		while (t) {
			if (t&1) {
				d*=fac[ti];
				n1++;
			}
			t>>=1; 
			ti++;
		}
		ll l=N/d;
		if (n1&1) {
			tl -= l*(l+1)/2*d;
		} else {
			tl += l*(l+1)/2*d;
		}
	}
	return tl%MODEXP;
}

int main() {
	//clock_t begin = clock();
	
	int N;
	if (scanf("%d", &N) != 1 || N<=0 || N>100000) {
		puts("ERROR");
		return 0;
	}
	flagprime();
	int nfac, fac[15], exp;
	ll b=1;
	for(int n=2; n<=N; ++n) {
		nfac=factor(n,fac);
		exp=find(N,fac,nfac);
		
		b *= F(n,exp);
		b %= MOD;
		
	}
	printf("%d\n", (int)b);
	
	//clock_t end = clock();
	//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//fprintf(stderr, "%lf", elapsed_secs);
}
