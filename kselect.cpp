#include <stdio.h>
#include <algorithm>
#include <string.h>

#define MXDP 6765201

char dp[MXDP];
int spa[4][51];
int spl[4];

int state2int(int state[4]) {
	return state[0] + 51 * (state[1] + 51 * (state[2] + 51 * state[3]));
}

void int2state(int statecode, int statebuf[4]) {
	
	int i=0; 
	while (statecode) {
		statebuf[i] = statecode % 51;
		i++;
		statecode /= 51;
	}
}

void printTabs(int indent) {
	while(indent--)putchar('\t');
}

void recFind(int s0, int s1, int s2, int s3, int rc, int depth, int K, int& maxbuf) {
	
	if (rc < 0) return;
	
	int state[] = {s0, s1, s2, s3};
	int hashcode = state2int(state);
	
	if (dp[hashcode]) {
		//printf("HIT!\n");
		//printf("state < %d %d %d %d >, rc=%d, depth=%d, maxbuf=%d\n", s0, s1, s2, s3, rc, depth, maxbuf);
		return;
	}
	
	//printTabs(depth);
	//printf("state < %d %d %d %d >, rc=%d, depth=%d, maxbuf=%d\n", s0, s1, s2, s3, rc, depth, maxbuf);
	
	dp[hashcode] = 1;
	
	if (depth == K) {
		if (rc&3) {
			if (maxbuf < rc) {
				maxbuf = rc;
			}
			//return rc;
		}
		return;
	}
	
	for (int i=0; i<4; ++i) {
		
		if (i) {
			state[i-1]--;
		}
		state[i]++;
		
		if ((rc&3) != i && spl[i] >= state[i] && rc > spa[i][state[i]-1]) {
			recFind(state[0], state[1], state[2], state[3], rc - spa[i][state[i]-1], depth+1, K, maxbuf);
		}
	}
}

int find(int N, int K, int sum) {
	
	int maxbuf = -1;
	
	recFind(0, 0, 0, 0, sum, 0, K, maxbuf);
	
	return maxbuf;
}

int main() {
	int T, N, K, a, sum;
	scanf("%d",&T);
	while(T--){
		memset(dp, 0, sizeof(dp));
		memset(spl, 0, sizeof(spl));
		
		scanf("%d %d", &N, &K);
		sum = 0;
		for (int i=0, ca; i<N; ++i) {
			scanf("%d", &a);
			
			ca = a&3;
			spa[ca][spl[ca]++] = a;
			
			sum += a;
		}
		
		for (int i=0; i<4; ++i) {
			std::sort(spa[i], spa[i]+spl[i]);
			
			//printf("MOD4==%d || ", i);
			//for (int j=0; j<spl[i]; ++j) {
			//	printf("%d, ", spa[i][j]);
			//}
			//printf("\n");
		}
		
		
		
		//printf("sum=%d\n", sum);
		printf("%d\n", find(N, K, sum));
		
	}
}


