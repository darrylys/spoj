#include <stdio.h>
#include <string.h>

#define MXQ 50010
#define MAXN 10010

typedef struct _NODE {
	int next;
	int val;
} NODE;

NODE db[MXQ];
int dbptr = 0;

int headNodeID[MAXN];
int tailNodeID[MAXN];

int initStacks(int N) {
	memset(headNodeID, -1, (N+1)*sizeof(headNodeID[0]));
	memset(tailNodeID, -1, (N+1)*sizeof(tailNodeID[0]));
	dbptr = 0;
}

void push(int stackNo, int val) {
	// dbptr is next empty node
	
	db[dbptr].val = val;
	
	// empty stack
	if (headNodeID[stackNo] == -1) {
		db[dbptr].next = -1;
		tailNodeID[stackNo] = dbptr;
		headNodeID[stackNo] = dbptr;
		
	} else {
		db[dbptr].next = headNodeID[stackNo];
		headNodeID[stackNo] = dbptr;
		
	}
	
	dbptr++;
}

void pop(int stackNo) {
	// not empty
	if (headNodeID[stackNo] >= 0) {
		headNodeID[stackNo] = db[headNodeID[stackNo]].next;
		if (headNodeID[stackNo] == -1) {
			tailNodeID[stackNo] = -1;
		}
	}
}

int top(int stackNo) {
	if (headNodeID[stackNo] == -1) {
		return -1;
	} else {
		return db[headNodeID[stackNo]].val;
	}
}

// put the sourceStackNo on top of targetStackNo
void put(int targetStackNo, int sourceStackNo) {
	if (targetStackNo == sourceStackNo) return;
	if (headNodeID[sourceStackNo] == -1) return;
	
	bool targEmpty = headNodeID[targetStackNo] == -1;
	db[tailNodeID[sourceStackNo]].next = headNodeID[targetStackNo];
	headNodeID[targetStackNo] = headNodeID[sourceStackNo];
	if (targEmpty) {
		tailNodeID[targetStackNo] = tailNodeID[sourceStackNo];
	}
	
	headNodeID[sourceStackNo] = -1;
	tailNodeID[sourceStackNo] = -1;
}

int main() {
	int T, N, Q, c=1;
	char cmd[6];
	int stackNo, val, ts, ss;
	
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d", &N, &Q);
		initStacks(N);
		
		printf("Case %d:\n", c++);
		
		while(Q--) {
			scanf("%s", cmd);
			if (cmd[0] == 't') {
				// top
				scanf("%d", &stackNo);
				int tpv = top(stackNo);
				if (tpv == -1) {
					printf("Empty!\n");
				} else {
					printf("%d\n", tpv);
				}
			} else if (cmd[1] == 'o') {
				// pop
				scanf("%d", &stackNo);
				pop(stackNo);
			} else if (cmd[2] == 't') {
				// put
				scanf("%d %d", &ts, &ss);
				put(ts,ss);
			} else {
				// push
				scanf("%d %d", &stackNo, &val);
				push(stackNo,val);
			}
		}
	}
	return 0;
}
