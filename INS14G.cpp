#include<stdio.h>
#define MOD (1000000007)
#define ll long long
#define MAXN (1000001)

int fac[MAXN];
int facinv[MAXN];

ll _pow(ll base, ll exp, int mod) {
	if (exp==1) return base;
	if (exp==0) return 1;
	
	ll half=_pow(base, exp>>1, mod);
	if (exp&1) {
		return (((half * half)%mod) * base)%mod;
	} else {
		return (half * half)%mod;
	}
}

ll pow(ll base, ll exp, int mod) {
	return _pow(base%mod, exp, mod);
}

int main() {
	fac[0] = 1;
	for (int i=1; i<MAXN; ++i) {
		fac[i] = (int)(((ll)fac[i-1] * i)%MOD);
	}
	facinv[MAXN-1] = pow(fac[MAXN-1], MOD-2, MOD);
	for (int i=MAXN-2; i>=0; --i) {
		facinv[i] = (int)(((ll)facinv[i+1] * (i+1))%MOD);
	}
	int T, N;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		N--;
		printf("%lld\n", (((ll)fac[N] * facinv[N/2])%MOD * facinv[N-(N/2)]) % MOD);
	}
}
