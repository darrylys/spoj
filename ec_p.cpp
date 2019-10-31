#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>

using namespace std;

#define MAXN 705

int visitTime[MAXN];
int parent[MAXN];
vector<int> adjnode[MAXN];
int pathstack[MAXN];
int disjointset[MAXN];
bool nroot[MAXN];
int pathtop;
int vt;
int RS[MAXN];
int RL[MAXN];
int R[MAXN];

bool comp(int a, int b) {
	if (RS[a] == RS[b]) {
		return RL[a] < RL[b];
	} else {
		return RS[a] < RS[b];
	}
}

int min(int a, int b) {
	return (a<b) ? a:b;
}

int max(int a, int b) {
	return (a>b) ? a:b;
}

int find(int n) {
	if (disjointset[n] != n) {
		disjointset[n] = find(disjointset[n]);
	}
	return disjointset[n];
}

void join(int a, int b) {
	//disjointset[a] = find(b);
	
	int ap = find(a);
	int bp = find(b);
	disjointset[ap] = bp;
	
}

void reset(int N) {
	pathtop = 0;
	vt = 1;
	memset(nroot, false, (N+1)*sizeof(nroot[0]));
	memset(visitTime, 0, (N+1)*sizeof(visitTime[0]));
	memset(parent, -1, (N+1)*sizeof(parent[0]));
	for (int i=0; i<N; ++i) {
		R[i] = i;
		disjointset[i] = i;
		adjnode[i].clear();
	}
}


void explore(int root) {
	int size = adjnode[root].size();
	for (int i=0; i<size; ++i) {
		if (adjnode[root][i] != parent[root]) {
			// if not yet visited
			if (visitTime[adjnode[root][i]] == 0) {
				parent[adjnode[root][i]] = root;
				pathstack[pathtop++] = adjnode[root][i];
				visitTime[adjnode[root][i]] = ++vt;
				explore(adjnode[root][i]);
				
				if (pathstack[pathtop-1] == adjnode[root][i]) {
					// explore: pathtop can be negative??
					pathtop--;
				}
				//printf("neg pathtop=%d\n", pathtop);
			} else if (visitTime[adjnode[root][i]] < visitTime[root]) { // loop detected
				//printf("2nd pathtop=%d\n", pathtop);
				while (pathtop && visitTime[pathstack[pathtop-1]] > visitTime[adjnode[root][i]]) {
					join(pathstack[pathtop-1], adjnode[root][i]);
					pathtop--;
				}
			} else {
				
			}
		}
	}
	
}

int main() {
	int T, N, M, a, b, c=1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		
		reset(N);
		for (int i=0; i<M; ++i) {
			scanf("%d %d", &a, &b); //all node pairs are different
			adjnode[a-1].push_back(b-1);
			adjnode[b-1].push_back(a-1);
		}
		
		parent[0] = -1;
		pathstack[pathtop++] = 0;
		visitTime[0] = 1;
		explore(0);
		
		for (int i=0; i<N; ++i) {
			nroot[find(i)] = true;
		}
		
		int r = 0;
		for (int i=1; i<N; ++i) {
			if (nroot[i]) {
				RS[r] = min(i, parent[i]);
				RL[r] = max(i, parent[i]);
				r++;
			}
		}
		
		printf("Caso #%d\n", c++);
		if (r == 0) {
			printf("Sin bloqueos\n");
		} else {
			// forget to add compare function....
			sort(R, R+r, comp);
			printf("%d\n", r);
			for (int i=0; i<r; ++i) {
				printf("%d %d\n", RS[R[i]]+1, RL[R[i]]+1);
			}
		}
		
	}
}
