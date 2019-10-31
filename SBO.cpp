#include <stdio.h>

#define MAXN 500010
#define MAXA 100001

//#define DEBUG

typedef struct _NODE {
	int maxf;
	int lazy;
} NODE;

int pos[MAXA][3];

// starting pos: all zeros
NODE ST[MAXN*5];
int arr[MAXN];

int max(int a, int b) {
	return a>b ? a:b;
}

int min(int a, int b) {
	return a<b ? a:b;
}

#ifdef DEBUG
void printtabs(int i) {
	while(i--)putchar('\t');
}
void printTree(int root, int a, int b, int ind) {
	if (a == b-1) {
		printtabs(ind); printf("[%d,%d)=>[maxf=%d,lazy=%d]{}\n", a, b, ST[root].maxf, ST[root].lazy);
		return;
	}
	printtabs(ind); printf("[%d,%d)=>[maxf=%d,lazy=%d] {\n", a, b, ST[root].maxf, ST[root].lazy);
	printTree(root*2, a, (a+b)/2, ind+1);
	printTree(2*root+1, (a+b)/2, b, ind+1);
	printtabs(ind); printf("}\n");
}
#endif

// [a,b), [qa,qb)
// lazy propagation
// add 1 to lazy if query matches
// propagates to the maxf variable along the way to root node
// problem with updating
int update(int root, int a, int b, int qa, int qb, int inc) {
	// impossible cases
	if (qb <= a || qa >= b || a >= b || qa >= qb) {
		return -1;
	}
	
	if (a == qa && b == qb) {
		ST[root].lazy += inc;
		ST[root].maxf += inc;
		
		return ST[root].maxf;
		// ?
		//return ST[root] += inc;
	}
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	int leftmax = update(lc, a, mid, qa, min(qb, mid), inc);
	int rightmax = update(rc, mid, b, max(qa,mid), qb, inc);
	
	// this is problematic.
	//ST[root].maxf = max(leftmax, rightmax) + ST[root].lazy;
	ST[root].maxf = max(ST[lc].maxf, ST[rc].maxf) + ST[root].lazy;
	return ST[root].maxf;
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; ++i) {
		scanf("%d", &arr[i]);
	}
	int mx = -1;
	for (int i=N-1; i>=0; --i) {
		int oldlimit;
		
		if (pos[arr[i]][0]) { // already set before
			oldlimit = pos[arr[i]][2];
			pos[arr[i]][2] = pos[arr[i]][1];
			pos[arr[i]][1] = i;
		} else {
			oldlimit = N;
			pos[arr[i]][0] = 1;
			pos[arr[i]][1] = i;
			pos[arr[i]][2] = N;
		}
		
		#ifdef DEBUG
		printf("i=%d, read=%d, pos=[one=%d, useless=%d]\n", i, arr[i], pos[arr[i]][1], pos[arr[i]][2]);
		#endif
		
		update(1, 0, N, pos[arr[i]][1], pos[arr[i]][2], 1);
		
		#ifdef DEBUG
		printf("RUN COMMAND: update(%d, %d, %d, %d, %d, %d)\n", 1, 0, N, pos[arr[i]][1], pos[arr[i]][2], 1);
		printTree(1, 0, N, 0);
		#endif
		
		update(1, 0, N, pos[arr[i]][2], oldlimit, -1);
		
		#ifdef DEBUG
		printf("RUN COMMAND: update(%d, %d, %d, %d, %d, %d)\n", 1, 0, N, pos[arr[i]][2], oldlimit, -1);
		printTree(1, 0, N, 0);
		
		printf("ST[1].maxf=%d\n", ST[1].maxf);
		#endif
		
		if (ST[1].maxf > mx) {
			mx = ST[1].maxf;
		}
	}
	
	printf("%d\n", mx);
	return 0;
}

