#include <stdio.h>
#include <string.h>

#define _DEBUG
#define MAXN (10002)

int tally[MAXN];
int vsqrt[MAXN];

void buildSqrt() {
	for (int i=0; i*i<MAXN; ++i) {
		vsqrt[i*i] = i;
	}
	
	for (int i=2; i<MAXN; ++i) {
		if (!vsqrt[i]) vsqrt[i] = vsqrt[i-1];
	}
}

int main() {
	buildSqrt();
	
	int T, L, K;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &L, &K);
		for (int i=1; i<=L; ++i) tally[i] = 1;
		
		int pt = L;
		while ( K > 0 ) {
			
			// sqrt the top value
			tally[pt]--;
			tally[vsqrt[pt]]++;
			K--;
			
			// move pt to first nonzero tally
			while (tally[pt] == 0) --pt;
			
		}
		
		int sum=0;
		for (int i=1; i<=pt; ++i) {
			sum += i * tally[i];
		}
		
		printf("%d\n", sum);
	}
	
}
