#include <stdio.h>

#define BIG (2000000000)
#define SML (-BIG)

typedef struct _STATE {
	// easiest problems
	int minProbNo;
	int minBalloonNo;
	
	// hardest problems
	int maxProbNo;
	int maxBalloonNo;
} STATE, *PSTATE;

STATE probState[3*1000002];
int indexCode[1000002];

void adjustMin(int root, int lc, int rc){
	// min
	if (probState[lc].minBalloonNo >= probState[rc].minBalloonNo) {
		probState[root].minBalloonNo = probState[lc].minBalloonNo;
		probState[root].minProbNo = probState[lc].minProbNo;
	} else {
		probState[root].minBalloonNo = probState[rc].minBalloonNo;
		probState[root].minProbNo = probState[rc].minProbNo;
	}
}

void adjustMax(int root, int lc, int rc) {
	// max
	if (probState[lc].maxBalloonNo < probState[rc].maxBalloonNo) {
		probState[root].maxBalloonNo = probState[lc].maxBalloonNo;
		probState[root].maxProbNo = probState[lc].maxProbNo;
	} else {
		probState[root].maxBalloonNo = probState[rc].maxBalloonNo;
		probState[root].maxProbNo = probState[rc].maxProbNo;
	}
}

// range: [a,b)
// 0,1,2,3,4,5 (a=0, b=6)
// indexcode=[4,10,11,6,14,15]
// (1,0,6)
// (2,0,3) (3,3,6)
// (4,0,1) (5,1,3) (6,3,4) (7,4,6)
// (10,1,2) (11,2,3) (14,4,5) (15,5,6)
// 
void build(int root, int a, int b) {
	if (a == b-1) {
		indexCode[a] = root;
		STATE sa = {a, 0, a, 0};
		probState[root] = sa;
	} else {
		int lc = root<<1;
		int rc = lc+1;
		
		build(lc, a, (a+b)/2);
		build(rc, (a+b)/2, b);
		
		adjustMin(root, lc, rc);
		adjustMax(root, lc, rc);
	}
}

void adjustToQuery(int type, int pi) {
	int api = indexCode[pi];
	if (type == 1) {
		probState[api].minProbNo = BIG;
		probState[api].minBalloonNo = SML;
		
		probState[api].maxProbNo = SML;
		probState[api].maxBalloonNo = BIG;
	} else {
		probState[api].minBalloonNo++;
		probState[api].maxBalloonNo++;
	}
	
	api >>= 1;
	
	while (api) {
		int lc = api<<1;
		int rc = lc+1;
		
		adjustMin(api, lc, rc);
		adjustMax(api, lc, rc);
		
		api >>= 1;
	}
}

int main() {
	int N, M, ti, pi;
	scanf("%d %d", &N, &M);
	build(1, 1, N+1);
	
	int solved = 0;
	
	while (M--) {
		scanf("%d %d", &ti, &pi);
		adjustToQuery(ti, pi);
		if (ti == 1) solved++;
		
		if (solved == N) {
			printf("Make noise\n");
		} else {
			printf("%d %d\n", probState[1].minProbNo, probState[1].maxProbNo);
		}
	}
	
}


