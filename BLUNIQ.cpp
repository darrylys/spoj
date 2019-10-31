// AC: 0.36s, 22M
/*
algo:
dynamic segment tree.
the only difference with usual segment tree is how to initialize the nodes
instead of preparing all node in memory at the very beginning, nodes are created only when required.
when null nodes are accessed, their cummulative sum is zero so, just ignore them.

This allows for segment tree to handle huge ranges commonly impossible.
this problem handles range from 0 to 10^9.

The total number of nodes required is O(Q lg N) where Q is the number of queries.
Time complexity is O(Q lg N) also.

*/

#include <stdio.h>

#define ll long long
//#define _DEBUG

const int MAXX = (1000100006);
const int MAXN = (100010);
const int FIND_RC = -1;

// [istart, iend)
typedef struct _Node {
	int istart;
	int iend;
	int val;
	int lc;
	int rc;
} Node;

// try dynamic segment tree
Node tree[MAXN*10];
int pMTTree = 1;

#ifdef _DEBUG
void print_tabs(int x) {
	while (x--) putchar('\t');
}
void print_tree(int root, int indent) {
	print_tabs(indent); printf("root:%d range:[%d,%d) val:%d lc:%d rc:%d {\n", root, 
		tree[root].istart, tree[root].iend, tree[root].val, tree[root].lc, tree[root].rc);
		
	if (tree[root].lc) {
		print_tree(tree[root].lc, indent+1);
	}
	if (tree[root].rc) {
		print_tree(tree[root].rc, indent+1);
	}
	print_tabs(indent); printf("}\n");
}
#endif

int init_node(int a, int b) {
	int id = pMTTree;
	
	// create node
	tree[id].istart = a;
	tree[id].iend = b;
	tree[id].val = 0;
	tree[id].lc = tree[id].rc = 0;
	
	// more pointer to next empty slot
	pMTTree++;
	
	return id;
}

// root = index of Node in tree array above
int find_number(int root, int qx) {
	
	int a = tree[root].istart;
	int b = tree[root].iend;
	
	if (qx < a || qx >= b) {
		return FIND_RC;
	}
	
	if (tree[root].val == b-a) {
		return FIND_RC;
	}
	
	if (b == a+1 && qx == a) {
		// found! return the number! Update too!
		tree[root].val = 1;
		return qx;
	}
	
	int mid = (a+b)>>1;
	// lc
	if (tree[root].lc == 0) {
		tree[root].lc = init_node(a, mid);
	}
	
	int src = qx;
	if (src >= a && src < mid) {
	
		int lcRet = find_number(tree[root].lc, src);
		if (lcRet >= 0) {
			
			int lcVal = (tree[root].lc == 0) ? 0 : tree[tree[root].lc].val;
			int rcVal = (tree[root].rc == 0) ? 0 : tree[tree[root].rc].val;
			tree[root].val = lcVal + rcVal;
			
			return lcRet;
		}
		
		src = mid;
	}
	
	// rc
	if (tree[root].rc == 0) {
		tree[root].rc = init_node(mid, b);
	}
	
	if (src >= mid && src < b) {
		
		int rcRet = find_number(tree[root].rc, src);
		if (rcRet >= 0) {
			
			int lcVal = (tree[root].lc == 0) ? 0 : tree[tree[root].lc].val;
			int rcVal = (tree[root].rc == 0) ? 0 : tree[tree[root].rc].val;
			tree[root].val = lcVal + rcVal;
			
			return rcRet;
		}
		
	}
	
	return FIND_RC;
}

void remove_number(int root, int qx) {
	
	int a = tree[root].istart;
	int b = tree[root].iend;
	
	if (b == a+1 && qx == a) {
		tree[root].val = 0;
		return;
	}
	
	int mid = (a+b)>>1;
	if (qx < mid) {
		// left child
		if (tree[root].lc == 0) {
			tree[root].lc = init_node(a, mid);
		}
		remove_number(tree[root].lc, qx);
		
	} else {
		// right child
		if (tree[root].rc == 0) {
			tree[root].rc = init_node(mid, b);
		}
		remove_number(tree[root].rc, qx);
		
	}
	
	int lcVal = (tree[root].lc == 0) ? 0 : tree[tree[root].lc].val;
	int rcVal = (tree[root].rc == 0) ? 0 : tree[tree[root].rc].val;
	tree[root].val = lcVal + rcVal;
	
}

int main() {
	// init root node
	tree[0].istart = 0;
	tree[0].iend = MAXX;
	tree[0].val = 0;
	tree[0].lc = tree[0].rc = 0;
	
	int N, cmd, qx;
	
	scanf("%d", &N);
	for (int __=0; __<N; ++__) {
		scanf("%d %d", &cmd, &qx);
		if (cmd == 1) {
			int num = find_number(0, qx-1);
			printf("%d\n", num+1);
			
			#ifdef _DEBUG
			printf("read: cmd=%d, qx=%d\n", cmd, qx-1);
			print_tree(0, 0);
			#endif
			
		} else {
			remove_number(0, qx-1);
			
			#ifdef _DEBUG
			printf("read: cmd=%d, qx=%d\n", cmd, qx-1);
			print_tree(0, 0);
			#endif
		}
	}
	
	return 0;
}

