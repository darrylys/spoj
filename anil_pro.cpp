#include<stdio.h>

#define MAXN (1000010)
#define ll long long
#define MOD (1000000007)
//#define DEBUG

typedef struct _NODE {
	int a0;
	int a1;
	int sum;
} NODE;

typedef struct _MAT {
	int m[2][2];
} MATRIX;

typedef struct _PAIR {
	int a0, a1;
} PAIR;

NODE tree[5 * MAXN];
MATRIX fibMat[MAXN];

inline int min(int a, int b) { return a<b ? a:b; }
inline int max(int a, int b) { return a>b ? a:b; }

#ifdef DEBUG
void printTabs(int indent) {
	while(indent--)putchar('\t');
}
void _printTree(int root, int a, int b, int indent) {
	if (b == a+1) {
		printTabs(indent);printf("[%d,%d]: a0=%d a1=%d sum=%d\n", a, b-1, tree[root].a0, tree[root].a1, tree[root].sum);
		return;
	}
	printTabs(indent); printf("[%d,%d]: a0=%d a1=%d sum=%d {\n", a, b-1, tree[root].a0, tree[root].a1, tree[root].sum);
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	_printTree(lc, a, mid, indent+1);
	_printTree(rc, mid, b, indent+1);
	printTabs(indent); printf("}\n", a, b-1);
}
void pt(int N) {
	_printTree(1, 0, N, 0);
}
void printMat(MATRIX& a) {
	printf("%d %d\n", a.m[0][0], a.m[0][1]);
	printf("%d %d\n", a.m[1][0], a.m[1][1]);
}
void mul(MATRIX& a, MATRIX& b, MATRIX& c) {
	for (int i=0; i<2; ++i) {
		for (int j=0; j<2; ++j) {
			c.m[i][j] = 0;
			for (int k=0; k<2; ++k) {
				c.m[i][j] += ((ll)a.m[i][k] * b.m[k][j])%MOD;
				if (c.m[i][j] >= MOD) c.m[i][j] -= MOD;
			}
		}
	}
}
#endif

void mul2(MATRIX& a, MATRIX& b, MATRIX& c) {
	c.m[0][0] = a.m[0][0] + a.m[0][1];
	c.m[0][1] = a.m[0][0];
	c.m[1][0] = a.m[0][0];
	c.m[1][1] = a.m[0][1];
	if (c.m[0][0] >= MOD) c.m[0][0] -= MOD;
}

void identityMat(MATRIX& a) {
	a.m[0][0] = 1;
	a.m[0][1] = 0;
	a.m[1][0] = 0;
	a.m[1][1] = 1;
}

void initFiboMat(MATRIX& a) {
	a.m[0][0] = 1;
	a.m[0][1] = 1;
	a.m[1][0] = 1;
	a.m[1][1] = 0;
}

void buildFibMat() {
	identityMat(fibMat[0]);
	MATRIX fibo;
	initFiboMat(fibo);
	
	for (int i=1; i<MAXN; ++i) {
		mul2(fibMat[i-1], fibo, fibMat[i]);
		#ifdef DEBUG
		if (i >= MAXN-100) {
			printf("=================\n");
			printMat(fibMat[i]);
		}
		#endif
	}
}

// always [a, b), and [qa, qb)
PAIR add(int root, int a, int b, int qa, int qb, int da0, int da1) {
	#ifdef DEBUG
	printf(">> add(%d,%d,%d,%d,%d,%d,%d)\n", root, a, b, qa, qb, da0, da1);
	#endif
	
	if (qa >= b || qb <= a || qa >= qb || a >= b) {
		PAIR p = {da0, da1};
		return p;
	}
	
	if (a == qa && b == qb) {
		// divide cases
		if (b-a == 1) { // 1 element tree, just add da0
			tree[root].sum += da0;
			tree[root].a0 += da0;
			
			if (tree[root].sum >= MOD) tree[root].sum -= MOD;
			if (tree[root].a0 >= MOD) tree[root].a0 -= MOD;
			
			PAIR p = {da1, (da0+da1)%MOD};
			return p;
		}
		
		if (b-a == 2) {// 2 element tree
			tree[root].sum += (da0 + da1)%MOD;
			tree[root].a0 += da0;
			tree[root].a1 += da1;
			
			if (tree[root].sum >= MOD) tree[root].sum -= MOD;
			if (tree[root].a0 >= MOD) tree[root].a0 -= MOD;
			if (tree[root].a1 >= MOD) tree[root].a1 -= MOD;
			
			PAIR p = {(da0+da1)%MOD, (int)(((ll)da1+da0+da1)%MOD)};
			return p;
		}
		
		// generic case
		
		ll n = b-a;
		
		//tsum = fib[b-a+1] - da1
		ll tsum = ((ll)da1*fibMat[b-a].m[0][0] + (ll)da0*fibMat[b-a].m[1][0] - da1 + MOD)%MOD;
		
		//nda0 = fib[b-a-2+1];
		ll nda0 = ((ll)da1 * fibMat[b-a-1].m[0][0] + (ll)da0 * fibMat[b-a-1].m[1][0])%MOD;
		//nda1 = fib[b-a-2+2];
		ll nda1 = ((ll)da1 * fibMat[b-a].m[0][0] + (ll)da0 * fibMat[b-a].m[1][0])%MOD;
		
		tree[root].sum += tsum;
		tree[root].a0 += da0;
		tree[root].a1 += da1;
		
		if (tree[root].sum >= MOD) tree[root].sum -= MOD;
		if (tree[root].a0 >= MOD) tree[root].a0 -= MOD;
		if (tree[root].a1 >= MOD) tree[root].a1 -= MOD;
		
		PAIR p = {(int)nda0, (int)nda1};
		return p;
	}
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	
	PAIR left = add(lc, a, mid, qa, min(qb, mid), da0, da1);
	#ifdef DEBUG
	printf("left=(%d,%d)\n", left.a0, left.a1);
	#endif
	
	PAIR right = add(rc, mid, b, max(qa, mid), qb, left.a0, left.a1);
	#ifdef DEBUG
	printf("right=(%d,%d)\n", right.a0, right.a1);
	printf("=======================\n");
	#endif
	
	ll tsum = (
		(((ll)tree[root].a1 * fibMat[b-a].m[0][0])%MOD) + 
		(((ll)tree[root].a0 * fibMat[b-a].m[1][0])%MOD) - 
		tree[root].a1 + MOD)%MOD;
	
	tree[root].sum = ((ll)tree[lc].sum + tree[rc].sum + tsum)%MOD;
	
	#ifdef DEBUG
	printf("tsum=%lld\n", tsum);
	#endif
	
	return right;
}

ll query(int root, int a, int b, int qa, int qb) {
	if (qa >= b || qb <= a || qa >= qb || a >= b) {
		return 0;
	}
	
	if (a == qa && b == qb) {
		return tree[root].sum;
	}
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	
	ll left = query(lc, a, mid, qa, min(qb, mid));
	ll right = query(rc, mid, b, max(qa, mid), qb);
	
	ll tempsum = 0;
	if (qa >= a+2) {
		ll fbb = ((ll)tree[root].a1 * fibMat[qb-a].m[0][0] + (ll)tree[root].a0 * fibMat[qb-a].m[1][0] - tree[root].a1)%MOD;
		ll fba = ((ll)tree[root].a1 * fibMat[qa-a].m[0][0] + (ll)tree[root].a0 * fibMat[qa-a].m[1][0] - tree[root].a1)%MOD;
		tempsum = fbb - fba;
	} else if (qa == a+1) {
		if (qb >= a+3) {
			ll fbb = ((ll)tree[root].a1 * fibMat[qb-a].m[0][0] + (ll)tree[root].a0 * fibMat[qb-a].m[1][0] - tree[root].a1)%MOD;
			tempsum = fbb - tree[root].a0;
		} else {
			tempsum = tree[root].a1;
		}
	} else { //qa==a
		if (qb >= a+3) {
			ll fbb = ((ll)tree[root].a1 * fibMat[qb-a].m[0][0] + (ll)tree[root].a0 * fibMat[qb-a].m[1][0] - tree[root].a1)%MOD;
			tempsum = fbb;
		} else if (qb == a+2) {
			tempsum = tree[root].a1 + tree[root].a0;
		} else {
			tempsum = tree[root].a0;
		}
	}
	
	return (left + right + tempsum + MOD) % MOD;
}

int main() {
	buildFibMat();
	
	int N, Q, c, st, en;
	scanf("%d %d", &N, &Q);
	while (Q--) {
		scanf("%d %d %d", &c, &st, &en);
		if (c) {
			printf("%lld\n", query(1, 0, N, st-1, en));
		} else {
			add(1, 0, N, st-1, en, 1, 1);
#ifdef DEBUG
			printf("==========================================================\n");
			printf("add [%d %d]\n", st-1, en-1);
			pt(N);
#endif
		}
	}
	
}
