#include <stdio.h>

int fz(int a) {
	if (a == 0) return 0;
	int x = 0;
	while (!(a&1)) {
		x++;
		a>>=1;
	}
	
	return x;
}

int main() {
	int T, N, x;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		int xk = 0;
		for (int i=0; i<N; ++i) {
			scanf("%d", &x);
			xk ^= fz(x);
		}
		if (xk) {
			printf("Puguh is the bestest player in teh wurld\n");
		} else {
			printf("Joke is the bestest player in teh wurld\n");
		}
	}
	return 0;
}
