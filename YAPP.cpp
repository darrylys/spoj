#include<stdio.h>

#define ll long long int

int bigmod(int base, int exp, int mod) {
	if (exp == 0) return 1;
	if (exp == 1) return base;
	
	int a = bigmod(base, exp/2, mod);
	if (exp % 2 == 0) {
		return (int)(((ll)a*a) % mod);
	} else {
		return (int)(((((ll)a*a) % mod) * (ll)base) % mod);
	}
}

int main() {
	int test, n;
	
	scanf("%d", &test);
	
	while (test--) {
		scanf("%d", &n);
		
		printf("%d\n", bigmod(2, n-1, 1000000007));
	}
	
	return 0;
}