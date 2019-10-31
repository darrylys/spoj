#include <stdio.h>

#define ll long long
#define MOD 1000000007
#define INV81 123456791

ll bigmod(ll base, ll exp, int mod) {
	if (base >= mod) base %= mod;
	
	if (exp == 0) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	if (exp&1) {
		return (((half*half) % mod) * base) % mod;
	} else {
		return (half*half) % mod;
	}
	
}

int main() {
	int T; ll N;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&N);
		N--;
		
		ll Nfe = N+1;
		N %= MOD;
		
		ll t9n = (10 + 9LL*N)%MOD;
		ll bgm = bigmod(10, Nfe, MOD);
		ll rh = (bgm - t9n + MOD)%MOD;
		
		rh = (50LL * (rh * INV81)%MOD )%MOD;
		printf("%lld\n", (6LL + N*6 + rh)%MOD);
	}
}

