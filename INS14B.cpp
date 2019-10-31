#include <stdio.h>

int main () {
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d" , &N);
		if (N&1) {
			printf("0\n");
			continue;
		}
		
		int sum =0;
		for (int i=1; i<=N; ++i) {
			if ((N*N) % i == 0) {
				int lef = i;
				int rig = N*N/i;
				
				sum += ((lef&1) == 0);
				sum += (lef != rig) && ((rig&1) == 0);
			}
		}
		
		printf("%d\n", sum);
	}
}
