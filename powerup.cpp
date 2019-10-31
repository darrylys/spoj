#include <stdio.h>

#define ll long long
#define MOD (1000000007)
#define PHIMOD (MOD-1)

ll bigmod(int base, int exp, int mod) {
	if (base == 0 && exp == 0) return 1; // 0^0
	
	if (exp == 0 || base == 1) return 1; // k^0 || 1^k
	if (exp == 1) return base%mod;
	
	ll half = bigmod(base, exp>>1, mod);
	if (exp&1) {
		return (((half*half)%mod) * base) % mod;
	} else {
		return (half*half)%mod;
	}
}

int main() {
	int a, b, c;
	while ( scanf("%d %d %d", &a, &b, &c) && a >= 0 && b >= 0 && c >= 0 ) {
		
		int hash = ((a > 0)<<2) | ((b > 0)<<1) | (c > 0);
		
		switch (hash) {
			case 0: printf("0\n"); break;
			case 1: printf("1\n"); break;
			case 2: printf("0\n"); break;
			case 3: printf("0\n"); break;
			case 4: printf("%d\n", a%MOD); break;
			case 5: printf("1\n"); break;
			case 6: printf("%d\n", a%MOD); break;
			case 7: {
				if (a%MOD == 0) {
					printf("0\n");
				} else {
					int exp = (int)bigmod(b, c, PHIMOD);
					ll res = bigmod(a, exp, MOD);
					printf("%lld\n", res);
				}
			} break;
		}
		
	}
}