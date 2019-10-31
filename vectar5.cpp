// using standard bigmod algo per test case is 0.12 s.
// precompute all 1 million exponents for 2^n and 3^n is 0.07 s.

// algorithm:
// start from All set (2^n-1)*(2^n-1) - [A subset B] - [B subset A] + (A==B)
// A subset B == B subset A, just labelling reversed.
// A subset B analysis: find how many ways to obtain subset A of length X out of 1..n and how many B can be formed out of A. Sum for all X.
// A subset B = \sigma i=1..n C(n,i) * (2^i-1)
// A subset B = \sigma i=1..n C(n,i) * (2^i) - \sigma i=1..n C(n,i)
// \sigma i=1..n C(n,i) * (2^i) is a binomial expansion of (2+1)^n - 1 or basically 3^n - 1
// \sigma i=1..n C(n,i) is 2^n - 1
// A subset B = 3^n - 1 - 2^n + 1 = 3^n - 2^n
// A==B = 2^n-1
// plugging in the numbers to above equation to obtain 2^(2n) - 2*3^n + 2^n

#include <stdio.h>

#define ll long long
#define MOD (1000000007)
#define MAXN (1000001)

//int e2[MAXN];
//int e3[MAXN];

void build(int * e, int n, int b) {
	e[0] = 1;
	for (int i=1; i<n; ++i) {
		e[i] = (int)(((ll)e[i-1] * b)%MOD);
	}
}

ll bigmod(int b, int e, int M) {
	if (e == 0) return 1;
	if (e == 1) return b;
	ll half = bigmod(b, e>>1, M);
	ll half2 = (half*half)%M;
	if (e&1) {
		half2 = (half2 * b)%M;
	}
	return half2;
}

int main() {
	//build(e2, MAXN, 2);
	//build(e3, MAXN, 3);
	
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		//printf("%lld\n", ((ll)e2[N] * e2[N] - 2LL * e3[N] + (ll)e2[N])%MOD);
		
		ll be2n = bigmod(2, N, MOD);
		ll be3n = bigmod(3, N, MOD);
		printf("%lld\n", (be2n*be2n - (be3n<<1) + be2n)%MOD);
	}
	
}
