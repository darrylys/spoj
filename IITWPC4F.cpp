//http://www.spoj.com/problems/IITWPC4F/

#include<stdio.h>
#define ll long long
#define MAXL (100010)
#define SGMX (5*MAXL)
//#define DEBUG

typedef struct _NODE {
	int no1;
	int noflips;
} NODE;

// calc number of flips

NODE xtree[SGMX];
NODE ytree[SGMX];

ll findSumInRec(int xwidth, int yheight, int xno1, int yno1) {
	ll sum = (ll)xno1 * (yheight - yno1) + (ll)(xwidth - xno1) * yno1;
	return sum;
}

#ifdef DEBUG
void printtabs(int indent) {while (indent--) putchar('\t'); }
void pt(NODE * tree, int root, int a, int b, int indent) {
	if (b == a+1) {
		printtabs(indent); printf("[%d %d](#1=%d upd=%d){}\n", a, b-1, tree[root].no1, tree[root].noflips);
		return;
	}
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	printtabs(indent); printf("[%d %d](#1=%d upd=%d){\n", a, b-1, tree[root].no1, tree[root].noflips);
	pt(tree, lc, a, mid, indent+1);
	pt(tree, rc, mid, b, indent+1);
	printtabs(indent); printf("}\n");
}
#endif

inline int max(int a, int b) { return (a>b) ? a:b; }
inline int min(int a, int b) { return (a<b) ? a:b; }

int query(NODE * tree, int root, int a, int b, int qa, int qb) {
	if (a >= b || qa >= qb || a >= qb || qa >= b) return 0;
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	
	if (a == qa && b == qb) {
		return tree[root].no1;
	}
	
	int left = query(tree, lc, a, mid, qa, min(qb, mid));
	int right = query(tree, rc, mid, b, max(qa, mid), qb);
	
	int no1 = left + right;
	if (tree[root].noflips & 1) {
		no1 = qb - qa - no1;
	}
	
	return no1;
}


void flip(NODE * tree, int root, int a, int b, int qa, int qb) {
	if (a >= b || qa >= qb || a >= qb || qa >= b) return;
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)>>1;
	
	if (a == qa && b == qb) {
		tree[root].no1 = (b-a-tree[root].no1);
		tree[root].noflips++;
		return;
	}
	
	flip(tree, lc, a, mid, qa, min(qb, mid));
	flip(tree, rc, mid, b, max(qa, mid), qb);
	tree[root].no1 = tree[lc].no1 + tree[rc].no1;
	
	if (tree[root].noflips & 1) {
		tree[root].no1 = b - a - tree[root].no1;
	}
	
	return;
}

int main() {
	int Q, l, r, x1, y1, x2, y2, LIMN = MAXL;
	char cmd[3];
	scanf("%d", &Q);
	while (Q--) {
		scanf("%s", cmd);
		switch(cmd[0]) {
			case 'x':
				scanf("%d %d", &l, &r);
				flip(xtree, 1, 0, LIMN, l, r+1);
				
				#ifdef DEBUG
				printf("cmd: x %d %d\n", l, r);
				pt(xtree, 1, 0, LIMN, 0);
				#endif
				break;
			
			case 'y':
				scanf("%d %d", &l, &r);
				flip(ytree, 1, 0, LIMN, l, r+1);
				
				#ifdef DEBUG
				printf("cmd: y %d %d\n", l, r);
				pt(ytree, 1, 0, LIMN, 0);
				#endif
				break;
			
			case 'q':
				scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
				
				int no1x = query(xtree, 1, 0, LIMN, x1, x2+1);
				int no1y = query(ytree, 1, 0, LIMN, y1, y2+1);
				
				#ifdef DEBUG
				printf("cmd: q %d %d %d %d\n", x1, y1, x2, y2);
				printf("XTREE\n");
				pt(xtree, 1, 0, LIMN, 0);
				
				printf("YTREE\n");
				pt(ytree, 1, 0, LIMN, 0);
				
				printf("x[%d-%d]: %d, y[%d-%d]: %d\n", x1, x2, no1x, y1, y2, no1y);
				#endif
				
				printf("%lld\n", findSumInRec(x2-x1+1, y2-y1+1, no1x, no1y));
				break;
			
		}
	}
}

