#include <stdio.h>

int gcd(int a, int b) {
	if (b==0) return a;
	return gcd(b, a%b);
}

int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	
	int begin = 360000000;
	for (int i=0, nh, nl, n; i<N; ++i) {
		scanf("%d.%d", &nh, &nl);
		n = nl + 1000000*nh;
		begin = gcd(n, begin);
	}
	
	int kh, kl, k;
	while (K--) {
		scanf("%d.%d", &kh, &kl);
		k = kh*1000000 + kl;
		if (k%begin) {
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	}
}
