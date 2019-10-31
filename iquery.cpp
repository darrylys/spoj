#include <stdio.h>

//#define DEBUG

#define ll long long
#define MOD (1000000007)
#define MXN (100005)
#define SGMX (400020)

// 0 = stdmultiply (* op), 1-x = for bit ops (& op)
int sgmtree[20][SGMX];

// all tree is the same. so they have exact same rev-sgm-idx
int idxinsgmtree[MXN];
int A[MXN];

void printSpaces(int i) {
	while (i--) putchar(' ');
}

#ifdef DEBUG
void recDumpTree(int *sgmTree, int root, int a, int b, int indent) {
	printSpaces(indent); printf(" >> root=%d [%d %d] [%d] {\n", root, a, b, sgmTree[root]);
	if (a != b-1) {
		int mid = (a+b)/2;
		recDumpTree(sgmTree, 2*root, a, mid, indent+4);
		recDumpTree(sgmTree, 2*root+1, mid, b, indent+4);
	}
	printSpaces(indent); printf("}\n");
}

void dumpTree(int N) {
	for (int i=0; i<=17; ++i) {
		printf("BITPOS=%d\n", i);
		recDumpTree(sgmtree[i], 1, 0, N, 0);
	}
}
#endif

inline int max(int a, int b) {
	return a>b ? a:b;
}

inline int min(int a, int b) {
	return a<b ? a:b;
}

void fillRevIdx(int root, int a, int b) {
	if (a == b-1) {
		idxinsgmtree[a] = root;
	} else {
		int mid = (a+b)/2;
		fillRevIdx(2*root, a, mid);
		fillRevIdx(2*root+1, mid, b);
	}
}

void buildSgmTree(int sgmcode, int *insSgmTree, int root, int a, int b) {
	if (a == b-1) {
		
		if (sgmcode == 0) {
			insSgmTree[root] = A[a];
		} else {
			insSgmTree[root] = (A[a] & (1 << (sgmcode-1))) > 0;
		}
		
	} else {
		int mid = (a+b)>>1;
		int lc = root<<1;
		int rc = lc+1;
		buildSgmTree(sgmcode, insSgmTree, lc, a, mid);
		buildSgmTree(sgmcode, insSgmTree, rc, mid, b);
		
		ll vlc = insSgmTree[lc];
		ll vrc = insSgmTree[rc];
		
		insSgmTree[root] = (int)((vlc * vrc + vlc + vrc) % MOD);
	}
}

void updateSgmTree(int sgmcode, int *insSgmTree, int updatedIdx, int updatedValue) {
	
	A[updatedIdx] = updatedValue;
	int root = idxinsgmtree[updatedIdx];
	
	if (sgmcode == 0) {
		if (insSgmTree[root] == updatedValue) {
			return;
		} else {
			insSgmTree[root] = updatedValue;
		}
	} else {
		int newbit = (updatedValue & (1 << (sgmcode-1))) > 0;
		
		if (insSgmTree[root] == newbit) {
			return;
		} else {
			insSgmTree[root] = newbit;
		}
	}
	
	//printf("updates! insSgmTree[%d]=%d\n", root, insSgmTree[root]);
	root >>= 1;
	
	while (root) {
		int lc = root<<1;
		int rc = lc+1;
		
		ll vlc = insSgmTree[lc];
		ll vrc = insSgmTree[rc];
		
		insSgmTree[root] = (int)((vlc * vrc + vlc + vrc) % MOD);
		
		root >>= 1;
	}
	
}

int query(int *insSgmTree, int root, int a, int b, int qa, int qb) {
	if (a == qa && b == qb) {
		return insSgmTree[root];
	}
	
	if (a >= qb || b <= qa || b <= a || qb <= qa) {
		return 0;
	}
	
	int lc = root<<1;
	int rc = lc+1;
	int mid = (a+b)/2;
	
	ll vlc = query(insSgmTree, lc, a, mid, max(a, qa), min(mid, qb));
	ll vrc = query(insSgmTree, rc, mid, b, max(mid, qa), min(b, qb));
	
	return (int)((vlc * vrc + vlc + vrc) % MOD);
	
}

int main() {
	int N, Q;
	
	scanf("%d", &N);
	
	fillRevIdx(1, 0, N);
	
	for (int i=0; i<N; ++i) {
		scanf("%d", &A[i]);
	}
	
	for (int i=0; i<=17; ++i) {
		buildSgmTree(i, sgmtree[i], 1, 0, N);
	}
	
	/*printf("BEGIN!\n");
	dumpTree(N);
	*/
	scanf("%d", &Q);
	char cmdbuf[5];
	int I, J;
	while (Q--) {
		scanf("%s %d %d", cmdbuf, &I, &J);
		if (cmdbuf[0] == 'M') {
			printf("%d\n", query(sgmtree[0], 1, 0, N, I-1, J));
		} else if (cmdbuf[0] == 'U') {
			//updateSgmTree(int sgmcode, int *insSgmTree, int updatedIdx, int updatedValue)
			for (int i=0; i<=17; ++i) {
				updateSgmTree(i, sgmtree[i], I-1, J);
				
//				printf("UPDATE: %d\n", i);
//				dumpTree(N);
			}
			
			
			
		} else {
			ll sum = 0;
			ll tp = 1;
			for (int i=1; i<=17; ++i) {
				sum +=  tp * query(sgmtree[i], 1, 0, N, I-1, J);
				tp <<= 1;
			}
			
			printf("%lld\n", sum%MOD);
			
		}
	}
	
}


