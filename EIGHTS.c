#include<stdio.h>
#define llu unsigned long long int

int main() {
	int t; llu k;
	scanf("%d", &t);
	while (t--) {
		scanf("%llu", &k);
		printf("%llu\n", 192 + (k-1)*250);
	}
	return 0;
}