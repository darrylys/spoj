#include <stdio.h>

int min(int a, int b) {
	return a<b ? a:b;
}

int max(int a, int b) {
	return a>b ? a:b;
}

int main() {
	int T, tN, tM, N, M, r;
	scanf("%d",&T);
	while(T--){
		
		scanf("%d %d", &tN, &tM);
		N = min(tN, tM);
		M = max(tN, tM);
		
		while(1) {
			
			if (N == M) {
				r = N;
				break;
			}
			
			if ((M-N)%(N-1) == 0) {
				r = N;
				break;
			}
			
			M = (M-N)%(N-1)+1;
			
			if (M < N) {
				int temp = M;
				M = N;
				N = temp;
			}
			
		}
		
		printf("%d\n", r);
		
	}
	return 0;
}
