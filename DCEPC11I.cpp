#include<stdio.h>

#define MAXN (100010)
#define ll long long
//#define DEBUG

typedef struct _NODE {
	ll sum;
	ll a0;
	int d;
} NODE;

NODE tree[5 * MAXN];

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
		printTabs(indent);printf("[%d,%d]: %lld\n", a, b-1, tree[root].sum);
		return;
	}
	printTabs(indent); printf("[%d,%d]: %lld {\n", a, b-1, tree[root].sum);
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

// always [a, b), and [qa, qb)
int add(int root, int a, int b, int qa, int qb, int da) {
	if (qa >= b || qb <= a || qa >= qb || a >= b) {
		return da;
	}
	
	if (a == qa && b == qb) {
		ll n = b-a;
		
		tree[root].sum += n*da + n*(n-1)/2;
		tree[root].a0 += da;
		tree[root].d++;
		
		//RET ret;
		//ret.sum = tree[root].sum;
		//ret.noForNext = da + (b-a);
		return da + (b-a);
	}
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	
	int left = add(lc, a, mid, qa, min(qb, mid), da);
	int right = add(rc, mid, b, max(qa, mid), qb, left);
	
	ll n = b-a;
	tree[root].sum = tree[lc].sum + tree[rc].sum + n*tree[root].a0 + tree[root].d*n*(n-1)/2;
	// sum = L + R + CS
	
	return da + (qb - qa);
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
	
	ll qba = qb-a;
	ll qaa = qa-a;
	ll partsum = (qba*tree[root].a0 + tree[root].d*qba*(qba-1)/2) - 
				 (qaa*tree[root].a0 + tree[root].d*qaa*(qaa-1)/2);
	
	return left + right + partsum;
}

int main() {
	int N, Q, c, st, en;
	scanf("%d %d", &N, &Q);
	while (Q--) {
		scanf("%d %d %d", &c, &st, &en);
		if (c) {
			printf("%lld\n", query(1, 0, N, st-1, en));
		} else {
			add(1, 0, N, st-1, en, 1);
#ifdef DEBUG
			printf("==========================================================\n");
			printf("add [%d %d]\n", st-1, en-1);
			pt(N);
#endif
		}
	}
}
