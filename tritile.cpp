#include <stdio.h>

#define ll long long

int main() {
	int T;
	ll N;
	scanf("%d", &T);
	while (T--){
		scanf("%lld", &N);
		/*if (N%2 == 1) N--;
		ll sd = 3 * (((N+3)/2) * 2 - 1);
		//printf("%lld\n", sd);
		printf("%s\n", sd%2 ? "No" : "Yes");
		*/
		printf("No\n");
	}
}