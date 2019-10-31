#include <stdio.h>
#include <vector>
#include <string.h>

#define ll long long
#define MAXN 100005

typedef struct _NODE {
	ll maxparent;
	ll maxsubtree;
	ll maxFromLeft;
	
	int parent;
	std::vector<int> children;
	std::vector<int> dogs;
	std::vector<ll> maxFromRight;
	
} NODE;

NODE nodes[MAXN];
int stack[MAXN];
int stack2[MAXN];

char visited[MAXN];
ll maxDogs[MAXN];

inline ll max(ll a, ll b) {
	return (a>b)?a:b;
}

void clear(int n) {
	memset(visited, 0, sizeof(visited));
	for (int i=1; i<=n; ++i) {
		nodes[i].children.clear();
		nodes[i].dogs.clear();
		nodes[i].maxFromRight.clear();
		nodes[i].parent = 0;
		nodes[i].maxFromLeft = 0;
		nodes[i].maxparent = 0;
		nodes[i].maxsubtree = 0;
	}
}

void printSpaces(int indent){
	while(indent--) putchar('\t');
}

void visitTrees(int root, int indent = 0) {
	if (nodes[root].children.size() == 1 && nodes[root].parent != -1) {
		printSpaces(indent);
		printf("<root=%d, parent=%d> {LEAF}\n", root, nodes[root].parent);
	} else {
		
		printSpaces(indent);
		printf("<root=%d, parent=%d> {\n", root, nodes[root].parent);
		int len = nodes[root].children.size();
		for (int i=0; i<len; ++i) {
			if (nodes[root].children[i] != nodes[root].parent) {
				printSpaces(indent);
				printf("%d. child=%d, dogs=%d, maxFromRight=%d\n", i, nodes[root].children[i], nodes[root].dogs[i], nodes[root].maxFromRight[i]);
				visitTrees(nodes[root].children[i], indent+1);
			}
		}
		
		printSpaces(indent);
		printf("}\n");
	}
}

void buildSubtrees(int root) {
	
	int esp = 0;
	stack[esp++] = root;
	nodes[root].parent = -1;
	
	while (esp) {
		//printf("esp=%d\n", esp);
		int top = stack[esp-1];
		
		// leaf nodes
		if (nodes[top].children.size() == 1 && nodes[top].parent != -1) {
			
			nodes[top].maxsubtree = 0;
			
			esp--;
		} else {
			
			if (visited[top]) {
				int len = nodes[top].children.size();
				ll tmax = 0;
				ll cmax;
				
				for (int i=len-1, cid; i>=0; --i) {
					cid = nodes[top].children[i];
					
					if (cid != nodes[top].parent) {
						cmax = nodes[cid].maxsubtree + (ll)nodes[top].dogs[i];
						if (tmax < cmax) {
							tmax = cmax;
						}
					}
					
					nodes[top].maxFromRight[i] = tmax;
				}
				nodes[top].maxsubtree = tmax;
				
				esp--;
			} else {
				
				visited[top] = 1;
				
				int len = nodes[top].children.size();
				for (int i=0, cid; i<len; ++i) {
					cid = nodes[top].children[i];
					nodes[top].maxFromRight.push_back(0);
					
					if (cid != nodes[top].parent) {
						nodes[cid].parent = top;
						stack[esp++] = cid;
					}
				}
			}
		}
	}
}

void fillWorstCases(int root) {
	int esp = 0;
	
	stack[esp] = -root;
	stack2[esp] = 0;
	esp++;
	
	nodes[root].maxparent = 0;
	nodes[root].maxFromLeft = 0;
	//printf("nodes[root].maxFromLeft=%lld\n", nodes[root].maxFromLeft);
	
	while (esp) {
		int top = stack[esp-1];
		int celemid = stack2[esp-1];
		esp--;
		
		if (top < 0) {
			top = -top;
			
			// find the max (subtree, parent.maxparent), is the result!
			maxDogs[top] = max(nodes[top].maxsubtree, nodes[top].maxparent);
			
		}
		
		if (celemid >= nodes[top].children.size()) {
			continue;
		}
		
		int cid = nodes[top].children[celemid];
		if (cid != nodes[top].parent) {
			// update cid.maxparent to exclude child.subtrees - visitedchild.subtree + existing maxparent
			
			ll right = (celemid+1 >= nodes[top].maxFromRight.size()) ? 0 : nodes[top].maxFromRight[celemid+1];
			nodes[cid].maxparent = (ll)nodes[top].dogs[celemid] + max(nodes[top].maxFromLeft, max(right, nodes[top].maxparent));
			//printf("maxparent=%lld\n", nodes[cid].maxparent);
			//printf("maxFromLeft[cid=%d]=%lld\n", cid, nodes[cid].maxFromLeft);
			nodes[top].maxFromLeft = max((ll)nodes[top].dogs[celemid] + nodes[cid].maxsubtree, nodes[top].maxFromLeft);
			
			// go to visitedchild.
			// push 2x
			
			// the parent first
			stack[esp] = top;
			stack2[esp] = celemid+1;
			esp++;
			
			// first meet child
			stack[esp] = -cid;
			stack2[esp] = 0;
			esp++;
			
		} else {
			
			// ignore, push next child elem
			stack[esp] = top;
			stack2[esp] = celemid+1;
			esp++;
			
		}
	}
}

int main() {
	int T, N, u, v, d;
	scanf("%d",&T);
	while(T--){
		//memset(visited, 0, sizeof(visited));
		
		scanf("%d",&N);
		
		clear(N);
		
		for (int i=1; i<N; ++i) {
			scanf("%d %d %d", &u, &v, &d);
			nodes[u].children.push_back(v);
			nodes[u].dogs.push_back(d);
			
			nodes[v].children.push_back(u);
			nodes[v].dogs.push_back(d);
		}
		buildSubtrees(1);
		
		//visitTrees(1);
		
		
		fillWorstCases(1);
		
		for (int i=1; i<N; ++i) {
			printf("%lld ", maxDogs[i]);
		}
		printf("%lld\n", maxDogs[N]);
		//putchar('\n');
		
	}
	return 0;
}
