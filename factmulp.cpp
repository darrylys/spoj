#include <stdio.h>

#define ll long long
#define MOD (1000000007)
#define C    (500000004)

int bigmod(int b, ll e, int mod) {
	if (e == 0) return 1;
	if (e == 1) return b % mod;
	
	int mid = bigmod(b, e>>1L, mod);
	ll mid2 = ((ll) mid * mid) % mod;
	if (e&1) {
		return (int)((mid2 * b) % mod);
	} else {
		return (int)(mid2);
	}
}

int main() {
	int T;
	ll p, e;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld", &p, &e);
		if (p % MOD == 1) {
			printf("%d\n", (int)(e % MOD));
		} else {
			// 1/2 * [(N-1)(N+2)/(p-1) - Ne] mod (10^9+7)
			int invpm1 = bigmod((int)((p-1)%MOD), MOD-2, MOD);
			int Nmodm = bigmod((int)(p%MOD), e, MOD);
			
			//printf("invpm1=%d, Nmodm=%d\n", invpm1, Nmodm);
			
			int a = (int)(((((ll)(Nmodm-1+MOD)*(Nmodm+2))%MOD)*invpm1)%MOD);
			int b = (int)(((ll)Nmodm*(e%MOD))%MOD);
			
			//printf("a=%d, b=%d\n", a, b);
			
			printf("%d\n", (int)(( (ll)C * (a - b + MOD) ) % MOD));
		}
	}
}
