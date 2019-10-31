#include<stdio.h>

#define MAXN (100010)
#define ll long long
#define MOD (1000000007)
//#define DEBUG

typedef struct _NODE {
	int sum;
	int a0;
} NODE;

NODE tree[5 * MAXN];
int expR[MAXN];
int sumExpR[MAXN+1]; //sum[N] = 0+1+2+...+(N-1)
int decsum[MAXN];

void buildREXP(int R, int N) {
	expR[0] = 1;
	for (int i=1; i<N; ++i) {
		expR[i] = ((ll)expR[i-1]*R)%MOD;
	}
	sumExpR[0] = 0;
	for (int i=1; i<=N; ++i) {
		sumExpR[i] = sumExpR[i-1] + expR[i-1];
		if (sumExpR[i] >= MOD) sumExpR[i] -= MOD;
	}
}

inline int min(int a, int b) {
	return a<b ? a:b;
}

inline int max(int a, int b) {
	return a>b ? a:b;
}

#ifdef DEBUG
void printTabs(int indent) {
	while(indent--)putchar('\t');
}
void _printTree(int root, int a, int b, int indent) {
	if (b == a+1) {
		printTabs(indent);printf("[%d,%d]: sum=%d a0=%d\n", a, b-1, tree[root].sum, tree[root].a0);
		return;
	}
	printTabs(indent); printf("[%d,%d]: sum=%d a0=%d{\n", a, b-1, tree[root].sum, tree[root].a0);
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
#endif

void addDecSum(int p, int maxp, int val) {
	while (p < maxp) {
		decsum[p] += val;
		if (decsum[p] >= MOD) decsum[p] -= MOD;
		p += (p & (-p));
	}
}
int getDecSum(int p) {
	int sum = 0;
	while (p > 0) {
		sum += decsum[p];
		if (sum >= MOD) sum -= MOD;
		p -= (p & (-p));
	}
	return sum;
}

// always [a, b), and [qa, qb)
int add(int root, int a, int b, int qa, int qb, int da) {
	if (qa >= b || qb <= a || qa >= qb || a >= b) {
		return da;
	}
	
	if (a == qa && b == qb) {
		int n = b-a;
		
		// sum = a0 * (1 + R + R^2 + ... + R^(n-1))
		tree[root].sum += ((ll)da * sumExpR[n])%MOD;
		if (tree[root].sum >= MOD) tree[root].sum -= MOD;
		tree[root].a0 += da;
		if (tree[root].a0 >= MOD) tree[root].a0 -= MOD;
		
		// next elem = da * R^n
		return (int)(((ll)da * expR[n])%MOD);
	}
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	
	int left = add(lc, a, mid, qa, min(qb, mid), da);
	int right = add(rc, mid, b, max(qa, mid), qb, left);
	
	// L + R + a0 * (1 + R + R^2 + ... + R^(n-1))
	ll n = b-a;
	tree[root].sum = (
		(ll)tree[lc].sum + 
		(ll)tree[rc].sum + 
		(ll)tree[root].a0*sumExpR[n]
	)%MOD;
	
	return ((ll)da*expR[qb-qa])%MOD;
}

int query(int root, int a, int b, int qa, int qb) {
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
	
	ll partsum = (ll)tree[root].a0 * (sumExpR[qb-a] - sumExpR[qa-a] + MOD);
	
	return (left + right + partsum)%MOD;
}

// [0, N) -> 0-based
int realQuery(int root, int a, int b, int qa, int qb) {
	int sumx = query(root, a, b, qa, qb);
	int dsum = (getDecSum(qb) - getDecSum(qa) + MOD)%MOD;
	
	#ifdef DEBUG
	printf("sumx=%d gdsum(%d)=%d, gdsum(%d)=%d, dsum=%d\n", sumx, qb, getDecSum(qb), qa, getDecSum(qa), dsum);
	#endif
	
	return (sumx - dsum + MOD)%MOD;
}

void setZero(int idx, int N) {
	int sumx = query(1, 0, N, idx, idx+1);
	int dsum = (getDecSum(idx+1) - getDecSum(idx) + MOD) % MOD;
	
	#ifdef DEBUG
	printf("sumx=%d gdsum(%d)=%d, gdsum(%d)=%d, dsum=%d\n", sumx, idx+1, getDecSum(idx+1), idx, getDecSum(idx), dsum);
	#endif
	
	addDecSum(idx+1, N+1, (sumx-dsum+MOD)%MOD);
}

int main() {
	int N, Q, R, c, st, i1, i2;
	scanf("%d %d %d", &N, &R, &Q);
	buildREXP(R, N);
	
	while (Q--) {
		scanf("%d", &c);
		
		switch(c) {
			case 0:
				scanf("%d %d %d", &st, &i1, &i2);
				add(1, 0, N, i1-1, i2, st);
				#ifdef DEBUG
					printf("==========================================================\n");
					printf("ADD [a0=%d start=%d end=%d]\n", st, i1-1, i2-1);
					pt(N);
				#endif
				
			break;
			
			case 1: {
				scanf("%d %d", &i1, &i2);
				#ifdef DEBUG
					printf("==========================================================\n");
					printf("QUERY [%d %d]\n", i1-1, i2-1);
				#endif
				
				int sum = realQuery(1, 0, N, i1-1, i2);
				printf("%d\n", sum);
			} break;
			
			case 2: {
				scanf("%d", &i1);
				#ifdef DEBUG
					printf("==========================================================\n");
					printf("MAKE ZERO [%d]\n", i1-1);
				#endif
				setZero(i1-1, N);
			} break;
		}
		
//		if (c) {
//			printf("%lld\n", query(1, 0, N, st-1, en));
//		} else {
//			add(1, 0, N, st-1, en, 1);
//		}
	}
}
