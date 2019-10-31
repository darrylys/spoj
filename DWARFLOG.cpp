#include <stdio.h>

#define MAXN 200005

//#define DEBUG

typedef struct _PAIR {
	int maxIdx;
	int minIdx;
} PAIR;

PAIR sgt[MAXN * 3];
int arrPos[MAXN];

inline int max(int a, int b) {
	return a>b ? a:b;
}

inline int min(int a, int b) {
	return a<b ? a:b;
}

#ifdef DEBUG
void printSpaces(int in) {
	while (in--) putchar(' ');
}

void printPair(int root, int a, int b, int in) {
	printSpaces(in);
	printf("[%d %d %d PAIR{%d, %d}]\n", root, a, b, sgt[root].maxIdx, sgt[root].minIdx);
	
	if (a != b-1) {
		int lh = root << 1;
		int rh = lh + 1;
		
		printPair(lh, a, (a+b)/2, in+4);
		printPair(rh, (a+b)/2, b, in+4);
	}
}
#endif

void build(int root, int a, int b) {
	#ifdef DEBUG
	printf("rab=%d %d %d\n", root, a, b);
	#endif
	if (a == b-1) {
		arrPos[a] = root;
		sgt[root].maxIdx = a;
		sgt[root].minIdx = a;
	} else {
		
		int lh = root << 1;
		int rh = lh + 1;
		
		build(lh, a, (a+b)/2);
		build(rh, (a+b)/2, b);
		
		sgt[root].maxIdx = max(sgt[lh].maxIdx, sgt[rh].maxIdx);
		sgt[root].minIdx = min(sgt[lh].minIdx, sgt[rh].minIdx);
	}
}

void update(int dwarfheight, int newIdx) {
	
	int dwroot = arrPos[dwarfheight];
	
	sgt[dwroot].maxIdx = newIdx;
	sgt[dwroot].minIdx = newIdx;
	dwroot /= 2;
	
	while (dwroot) {
		
		int lh = dwroot << 1;
		int rh = lh + 1;
		
		sgt[dwroot].maxIdx = max(sgt[lh].maxIdx, sgt[rh].maxIdx);
		sgt[dwroot].minIdx = min(sgt[lh].minIdx, sgt[rh].minIdx);
		
		dwroot /= 2;
	}
	
}

PAIR query(int dwroot, int a, int b, int qa, int qb) {
	#ifdef DEBUG
	printf("query(%d %d %d %d %d\n", dwroot, a, b, qa, qb);
	#endif
	
	if (a == qa && b == qb) {
		PAIR res = {sgt[dwroot].maxIdx, sgt[dwroot].minIdx};
		return res;
	}
	
	PAIR left = {-1, MAXN};
	
	if (b <= qa || a >= qb) {
		return left;
	}
	
	PAIR right = {-1, MAXN};
	
	int lh = dwroot*2;
	int rh = lh + 1;
	int mid = (a+b)/2;
	
	left = query(lh, a, mid, max(a, qa), min(mid, qb));
	right = query(rh, mid, b, max(mid, qa), min(b, qb));
	
	PAIR ret = {
		max(left.maxIdx, right.maxIdx),
		min(left.minIdx, right.minIdx)
	};
	
	return ret;
	
}

int main() {
	int N, M, C, X, Y;
	scanf("%d %d", &N, &M);
	
	build(1, 1, N+1);
	
	#ifdef DEBUG
	printf("INITIAL: \n");
	printPair(1, 1, N+1, 0);
	#endif
	
	while (M--) {
		scanf("%d %d %d", &C, &X, &Y);
		
		#ifdef DEBUG
		printf("read %d %d %d\n", C, X, Y);
		#endif
		
		if (C == 1) {
			int xni = sgt[arrPos[Y]].maxIdx;
			int yni = sgt[arrPos[X]].maxIdx;
			update(X, xni);
			update(Y, yni);
			
			#ifdef DEBUG
			printf("COMMAND: UPDATE %d %d\n", X, Y);
			printPair(1, 1, N+1, 0);
			#endif
			
		} else {
			PAIR res = query(1, 1, N+1, X, Y+1);
			
			#ifdef DEBUG
			printf("COMMAND: QUERY %d %d: res={%d, %d}\n", X, Y, res.maxIdx, res.minIdx);
			printPair(1, 1, N+1, 0);
			#endif
			
			printf("%s\n", (res.maxIdx - res.minIdx + 1) == (Y-X+1) ? "YES" : "NO");
		}
	}
	return 0;
}


