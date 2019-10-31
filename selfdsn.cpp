#include <stdio.h>

#define ll long long

ll bigmod(ll b, ll e, int m) {
	if (e == 0) return 1;
	if (e == 1) return b%m;
	
	ll half = bigmod(b, e>>1, m);
	if (e&1) {
		return (((half * half)%m) * b)%m;
	} else {
		return (half * half)%m;
	}
}

int main() {
	int T; ll N; int M;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %d", &N, &M);
		int m = M;
		
		if (N == 1) printf("%d\n", 100 % m);
		else if (N == 2) printf("%d\n", 136 % m);
		else if (N == 3) printf("%d\n", 1425 % m);
		else {
			ll B = N+3;
			ll ans = (((B-4+m)%m) * bigmod(B%m, B-1, m))%m + (2LL * bigmod(B%m, B-2, m))%m + bigmod(B%m, B-3, m) + bigmod(B%m, 3, m);
			printf("%lld\n", ans%m);
		}
	}
}

