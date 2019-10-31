/*
AC 0.21s 14M SPOJ

algo: segment tree lazy prop
precompute the LCMA to 300000 mod 10^9+7
when query gcd, find the minimum element of A in the range
when query lcm, find the maximum element of A in the range
print LCMA[x]

the problem probably is to calculate the LCM(1, 2, 3, ..., 300000) mod 10^9+7
the problem LCM(1, 2, ..., N) can be decomposed to LCM( LCM(1, 2, ..., N-1), N) = LCM(1, 2, ..., N-1) * C, where C is some number
the idea is to know when to update the prefix LCM value.
basically, does the LCM(1, 2, ..., N) == LCM(1, 2, ..., N-1) ??
or if it is not, multiplied by what? what is C?
it can be seen that the LCM values will be updated when N in form p^k where p is a prime.
because, prior to N, the biggest power of p encountered is (k-1).
therefore, in order to cater for p^k, the prefix LCM needs to be multiplied by p.

when N = p1^k * p2^l, p2^l has been encountered before because p2^l < N.
therefore, when N is composed by multiple primes, no LCM value needs to be updated.

This way, no need for using division and invert mods, just purely using multiplication!

WA (forget to add tree[root].p when updating the tree, silly mistake) 
AC
*/

#include <stdio.h>

#define MAXL (100005)
#define MAXA (300001)
#define MOD (1000000007)
#define BIG (1000000000)
//#define _DEBUG
//#define _TIMED
#define ll long long

typedef struct _NODE {
	int minv;
	int maxv;
	ll p;
} NODE;

NODE tree[MAXL*5];
int lcma[MAXA];
int A[MAXL];
//int invtree[MAXL];
int prime[MAXA];
int mulflag[MAXA];
char primeflag[MAXA];

inline ll min(ll a, ll b) { return (a<b) ? a:b; }
inline ll max(ll a, ll b) { return (a>b) ? a:b; }

int buildPrimes() {
	int p = 1;
	prime[0] = 2;
	
	int i;
	for (i=3; i*i < MAXA; i += 2) {
		if (!primeflag[i]) {
			prime[p++] = i;
			int d = i<<1;
			for (int j=i*i; j < MAXA; j += d) {
				primeflag[j] = 1;
			}
		}
	}
	
	for ( ; i<MAXA; i+=2) {
		if (!primeflag[i]) {
			prime[p++] = i;
		}
	}
	
	return p;
}

int buildLCMA(int nprimes) {
	mulflag[0] = 0;
	mulflag[1] = 1;
	
	for (int i=0; i<nprimes; ++i) {
		for (ll j=prime[i]; j < MAXA; j *= prime[i]) {
			mulflag[(int)j] = prime[i];
		}
	}
	
	lcma[0] = 0;
	lcma[1] = 1;
	for (int i=2; i<MAXA; ++i) {
		if (mulflag[i] > 0) {
			lcma[i] = ((ll)lcma[i-1] * mulflag[i])%MOD;
		} else {
			lcma[i] = lcma[i-1];
		}
	}
}

void build(int root, int a, int b) {
	if (b == a+1) {
		//invtree[a] = root;
		tree[root].minv = A[a];
		tree[root].maxv = A[a];
		tree[root].p = 0;
	} else {
		int lc = root<<1;
		int rc = lc+1;
		
		build(lc, a, (a+b)>>1);
		build(rc, (a+b)>>1, b);
		
		tree[root].minv = min(tree[lc].minv, tree[rc].minv);
		tree[root].maxv = max(tree[lc].maxv, tree[rc].maxv);
	}
}

#ifdef _DEBUG
int printindent(int x) {
	while (x--) {
		putchar('\t');
	}
}
void printTree(int root, int a, int b, int indent) {
	if (b == a+1) {
		printindent(indent); printf("< [%d %d) minv=%d maxv=%d p=%lld>\n", a, b, tree[root].minv, tree[root].maxv, tree[root].p);
	} else {
		printindent(indent); printf("< [%d %d) minv=%d maxv=%d p=%lld> {\n", a, b, tree[root].minv, tree[root].maxv, tree[root].p);
		int lc = root<<1;
		int rc = lc+1;
		
		printTree(lc, a, (a+b)>>1, indent+1);
		printTree(rc, (a+b)>>1, b, indent+1);
		
		printindent(indent); printf("}\n");
	}
}
#endif

void update(int root, int a, int b, int qa, int qb, int p) {
	
	if (qa == a && qb == b) {
		tree[root].minv += p;
		tree[root].maxv += p;
		tree[root].p += p;
		return;
	}
	
	if (qa >= b || qb <= a) {
		return;
	}
	
	int mid = (a+b)>>1;
	int lc = root<<1;
	int rc = lc+1;
	
	update(lc, a, mid, qa, min(qb, mid), p);
	update(rc, mid, b, max(qa, mid), qb, p);
	
	tree[root].minv = min(tree[lc].minv, tree[rc].minv) + tree[root].p;
	tree[root].maxv = max(tree[lc].maxv, tree[rc].maxv) + tree[root].p;
}

ll fmin(int root, int a, int b, int qa, int qb) {
	
	if (qa == a && qb == b) {
		return tree[root].minv;
	}
	
	if (qa >= b || qb <= a) {
		return BIG;
	}
	
	int mid = (a+b)>>1;
	int lc = root<<1;
	int rc = lc+1;
	
	int lv = fmin(lc, a, mid, qa, min(qb, mid));
	int rv = fmin(rc, mid, b, max(qa, mid), qb);
	
	return min(lv, rv) + tree[root].p;
}

ll fmax(int root, int a, int b, int qa, int qb) {
	if (qa == a && qb == b) {
		return tree[root].maxv;
	}
	
	if (qa >= b || qb <= a) {
		return -1;
	}
	
	int mid = (a+b)>>1;
	int lc = root<<1;
	int rc = lc+1;
	
	int lv = fmax(lc, a, mid, qa, min(qb, mid));
	int rv = fmax(rc, mid, b, max(qa, mid), qb);
	
	return max(lv, rv) + tree[root].p;
}

int main() {
	int nprimes = buildPrimes();
	buildLCMA(nprimes);
	
	#ifdef _DEBUG
	printf("lcms\n");
	for (int i=0; i<14; ++i) {
		printf("%d\n", lcma[i]);
	}
	printf("=============\n");
	#endif
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	for (int i=0; i<N; ++i) {
		scanf("%d", &A[i]);
	}
	
	build(1, 0, N);
	
	#ifdef _DEBUG
	printf("printTree(1, 0, %d, 0)\n", N);
	printTree(1, 0, N, 0);
	#endif
	
	while (M--) {
		int cmd, qa, qb;
		scanf("%d %d %d", &cmd, &qa, &qb);
		if (cmd == 0) {
			int p;
			scanf("%d", &p);
			update(1, 0, N, qa, qb+1, p);
			
			#ifdef _DEBUG
			printf("update(1, 0, %d, %d, %d, %d)\n", N, qa, qb+1, p);
			printf("printTree(1, 0, %d, 0)\n", N);
			printTree(1, 0, N, 0);
			#endif
			
		} else if (cmd == 2) {
			ll minv = fmin(1, 0, N, qa, qb+1);
			printf("%d\n", lcma[(int)minv]);
			
		} else {
			ll maxv = fmax(1, 0, N, qa, qb+1);
			printf("%d\n", lcma[(int)maxv]);
			
		}
		
	}
	
	return 0;
}
