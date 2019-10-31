#include <stdio.h>

int pi[10005];

int main() {
	int T, ki, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		int grundy = 0;
		for (int i=0; i<N; ++i) {
			scanf("%d", &pi[i]);
		}
		for (int i=0; i<N; ++i) {
			scanf("%d", &ki);
			grundy ^= (pi[i] % (ki+1));
		}
		if (grundy) {
			printf("Amit\n");
		} else {
			printf("Mishra\n");
		}
	}
}

