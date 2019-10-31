#include <stdio.h>

#define MOD (1000000007)
#define ll long long

ll bigmod(int base, int exp, int mod) {
	if (base == 1 || exp == 0) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	if (exp&1) {
		return (((half*half)%mod) * base)%mod;
	}
	return (half*half)%mod;
}

ll get2(int a, int b, int k) {
	ll sum = 0;
	for (int i=1; i<=b; ++i) {
		sum += ((ll)((b/i) - ((a-1)/i))) * bigmod(i, k, MOD);
		if (sum >= MOD) sum %= MOD;
	}
	return sum;
}

ll get(int N, int k) {
	ll sum = 0;
	for (int i=1; i<N; ++i) {
		sum += ((ll)(N-1) / i) * bigmod(i, k, MOD);
		if (sum >= MOD) sum -= MOD;
	}
	return sum;
}

int main() {
	int T,a,b,k;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d", &a, &b, &k);
		//printf("%lld\n", (get(b+1, k) - get(a, k) + MOD)%MOD);
		printf("%lld\n", get2(a,b,k));
	}
	return 0;
}
