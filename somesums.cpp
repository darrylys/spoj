/*
for now, the algo should be expansion of A(x) / (1-x)^(K+M+1), find coeff of x^N
A(x) is Euler polynomial for generating function for sequence: 0^k + 1^k + 2^k + ...
A(x) can be precomputed in O(k^2)

WA!
mistake, the C(N,R) obtains wrong value when N is around 1000000007 due to annoying boundary values!
rcoef: C(1000000015, 15): 0
A[10][0]=0
rcoef: C(1000000014, 15): 0
A[10][1]=1
rcoef: C(1000000013, 15): 0
A[10][2]=1013
rcoef: C(1000000012, 15): 0
A[10][3]=47840
rcoef: C(1000000011, 15): 0
A[10][4]=455192
rcoef: C(1000000010, 15): 0
A[10][5]=1310354
rcoef: C(1000000009, 15): 0
A[10][6]=1310354
rcoef: C(1000000008, 15): 0
A[10][7]=455192
rcoef: C(1000000007, 15): 0
A[10][8]=47840
rcoef: C(1000000006, 15): 0 // WTF?
A[10][9]=1013
rcoef: C(1000000005, 15): 0 // WTF?

here, defined 0^0 = 1, 0^k = 0 | k != 0
*/

#include<stdio.h>

#define MOD (1000000007)
#define ll long long
#define MAXK (1005)
#define MPK (2010)
//#define _DEBUG

int A[MAXK][MAXK];
int invmod[MPK];

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

void buildInvTbl() {
	invmod[1] = 1;
	for (int i=2; i<MPK; ++i) {
		invmod[i] = bigmod(i, MOD-2, MOD);
	}
}

void buildEuler() {
	A[0][0] = 1;
	A[1][1] = 1;
	for (int n=2; n<MAXK; ++n) {
		A[n][0] = 0;
		A[n][1] = A[n][n] = 1;
		for (int m=2; m<n; ++m) {
			A[n][m] = ((ll)(n-m+1)*A[n-1][m-1] + ((ll)(m)*A[n-1][m]))%MOD;
		}
	}
}

// C(N+1, R) = C(N,R) * (N+1) / (N-R+1)
ll getNp1(ll cnr, int N, int R) {
	//return (((cnr * (N+1))%MOD) * bigmod(N-R+1, MOD-2, MOD))%MOD;
	return (((cnr * (N+1))%MOD) * bigmod(N-R+1, MOD-2, MOD))%MOD;
}

// C(N,R+1) = C(N,R) * (N-R) / (R+1)
// improvement from 40s --> 14s by changing bigmod to array!
ll getRp1(ll cnr, int N, int R) {
	//return (((cnr * (N-R))%MOD) * bigmod(R+1, MOD-2, MOD))%MOD;
	return (((cnr * (N-R))%MOD) * invmod[R+1])%MOD;
}

ll find(int M, int N, int K) {
	#ifdef _DEBUG
	printf(">> FIND ( M=%d, N=%d, K=%d )\n", M, N, K);
	#endif
	
	if (M == 0 || N == 0) {
		if (N > 0) return bigmod(N, K, MOD);
		else return (K == 0);
	}
	
	int lim = (N < K) ? N : K;
	ll sum = 0;
	
	ll cbegin = 1;
	for (int r=1; r<=M+K; ++r) {
		cbegin = getRp1(cbegin, N+M+K-lim, r-1);
	}
	
	#ifdef _DEBUG
	printf("begin: C(%d, %d): %lld\n", N+M+K-lim, M+K, cbegin);
	#endif
	
	ll rcoef = cbegin;
	
	for (int i=lim; i>=0; --i) {
		
		#ifdef _DEBUG
		printf("rcoef: C(%d, %d): %lld\n", N+M+K-i, M+K, rcoef);
		printf("A[%d][%d]=%d\n", K, i, A[K][i]);
		#endif
		
		sum += (rcoef * A[K][i])%MOD;
		sum %= MOD;
		rcoef = getNp1(rcoef, N+M+K-i, M+K);
	}
	
	return sum;
}

int main() {
	//memset(A, 0, sizeof(A));
	buildEuler();
	buildInvTbl();
	
	int T, N, M, K;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &M, &N, &K);
		printf("%lld\n", find(M, N, K));
	}
	
	return 0;
}

