#include <stdio.h>
int main() {
	int T, N, c=1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		printf("Case %d: ", c++);
		
		if (N == 3) printf("2 3\n");
		else {
			printf("%d %d\n", (N-(N&1))>>1, (N-(N&1)));
		}
	}
}
