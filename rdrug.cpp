/*
AC 0.17s 10M SPOJ

ad-hoc, graph
this problem is quite hard

lets start the analysis with finding the suitable representation of the problem
The atoms can obviously be represented with nodes in a graph
and when atoms form compounds, that means that there is an edge between atoms

mr banner wanted to combine the separated compounds into one compound by adding edges
every atom can only have one additional in/out edge.
i.e. when an edge is constructed between 2 atoms, no new edges can use either of the two.
the cost of adding edge = sum of participating atoms.
find the minimum cost to connect all the compunds.

algo:
1. find the connected components
	this can be accomplished by simple dfs
	just remember that 10^5 recursion depth is not pretty
	check whether it is possible to connect the components. 
	The number of nodes required will be: 2*(number_of_connected_components - 1) at minimum
	check whether the atoms are already connected. In this case, just print 0

2. the number of nodes inside a component is the number of edges that can be constructed
	that connects to this component. A component of 5 nodes can accept 5 new edges maximum.

observation:
we want to find the minimum sum of edge cost, and edge cost is also another sum.
this allows for some interesting observation.

basically, this cost calculation mechanism shows that the exact configuration of which edge connects
which atom to which atom is irrelevant as long as the atoms participating in the 
constructed edges are the same which is simply the sum of the mass of participating atoms.
No matter how the exact configuration of edges be like, as long as the atoms included in it is the same,
the sum cost does not change.

and this is half of the key to solve this problem.

obviously, since this is the case, 
to find the minimum sum, the atoms participating should have the least amount of mass
for each component, atoms with the least amount of mass should be preferred.

How to find such set?

Let:
let C is the set of all connected components.
let Ci is i-th connected component

Si is the subset of connected component Ci that is used in the minimal set.
Si can be Ci.
no doubt that Si will be composed of the |Si| least massive atoms in Ci.

for each Ci, find all possible Si and find the total weight of atoms inside each of them
there are only |Ci| possible Si.

this can be done simply by sorting Ci members from the lightest to heaviest atoms.
Si[0] = mass(Ci[0])
Si[1] = mass(Ci[0]) + mass(Ci[1])
Si[2] = mass(Ci[0]) + mass(Ci[1]) + mass(Ci[2])
and so on...

do this for all Si in every Ci

now, all we have to do is to find the subset of these Si such that the sum is minimum,
the size of this subset is |C|, and the edges formed with these atoms in this subset can connect the whole C.

What this algorithm do is to remove useless Si from the set until only the bare minimum remains.
The rationale is based on the following statement:

	The number of nodes required will be: 2*(number_of_connected_components - 1) at minimum

We don't need all nodes. If some of them can be removed, pick the heaviest first!

let S = set of Si sorted.

from the heaviest Si to lightest
	if only one atom in connected component owner of Si, 
		ignore this Si, proceed to next
		
	else 
		remove the heaviest atom in connected component that owns Si
	
proceed with the loop until node remaining == 2*(number_of_connected_components - 1)

the minimum sum is thus the total sum of the remaining nodes


Time complexity: O(T * N lg N)
Space complexity: O(N + M)

*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

#define ll long long
//#define _DEBUG
//#define _TIMED

using namespace std;

const int MAXN = 100001;

typedef struct _CC {
	int connCompNo;
	int val;
} CC;

int mass[MAXN];
vector<int> bond[MAXN];
vector<int> connComp[MAXN];
bool visited[MAXN];
CC connCompVal[MAXN];
int gstack[MAXN];

void sdfs(int rroot, vector<int> &mem) {
	
	int top=0;
	gstack[top++] = rroot;
	
	while (top) {
		int etop = gstack[top-1];
		top--;
		
		if (!visited[etop]) {
			visited[etop] = true;
			mem.push_back(etop);
			for (int i=bond[etop].size()-1; i>=0; --i) {
				if (!visited[bond[etop][i]]) {
					//dfs(bond[root][i], mem);
					gstack[top++] = bond[etop][i];
				}
			}
		}
		
	}
	
}

bool connCompare(int a, int b) {
	return mass[a] < mass[b];
}

bool CCComp(const CC &a, const CC &b) {
	return a.val < b.val;
}

int appendMass(int connCompN) {
	int cn=0;
	
	for (int i=0; i<connCompN; ++i) {
		
		int size = connComp[i].size();
		int tmp = 0;
		
		for (int j=0; j<size; ++j) {
			connCompVal[cn].connCompNo = i;
			connCompVal[cn].val = tmp + mass[connComp[i][j]];
			
			tmp += mass[connComp[i][j]];
			
			cn++;
		}
	}
	
	return cn;
}

void filterOut(int connCompValN, int connCompN, int N) {
	ll requiredN = (connCompN-1)<<1;
	
	for (int i=connCompValN-1; i>=0; --i) {
		
		if (requiredN == N) {
			break;
		}
		
		int ccid = connCompVal[i].connCompNo;
		if (connComp[ccid].size() > 1) {
			connComp[ccid].pop_back();
			N--;
		}
	}
}

int calcSumMass(int connCompN) {
	int totalMass=0;
	for (int i=0; i<connCompN; ++i) {
		for (int j=connComp[i].size()-1; j>=0; --j) {
			totalMass += mass[connComp[i][j]];
		}
	}
	return totalMass;
}

int main() {
	int T, N, M;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		
		#ifdef _DEBUG
		printf("\nN=%d, M=%d\n", N, M);
		#endif
		
		memset(visited, false, N*sizeof(visited[0]));
		for (int i=0; i<N; ++i) {
			bond[i].clear();
		}
		
		for (int i=0, a, b; i<M; ++i) {
			scanf("%d %d", &a, &b);
			bond[a-1].push_back(b-1);
			bond[b-1].push_back(a-1);
		}
		
		for (int i=0; i<N; ++i) {
			scanf("%d", &mass[i]);
		}
		
		#ifdef _DEBUG
		for (int i=0; i<N; ++i) {
			printf("%d, mass=%d -->", i, mass[i]);
			for (int j=0; j<bond[i].size(); ++j) {
				printf(" %d", bond[i][j]);
			}
			printf("\n");
		}
		#endif
		
		int connCompN=0;
		for (int i=0; i<N; ++i) {
			if (!visited[i]) {
				connComp[connCompN].clear();
				sdfs(i, connComp[connCompN++]);
			}
		}
		
		#ifdef _DEBUG
		printf("connCompN=%d\n", connCompN);
		for (int i=0; i<connCompN; ++i) {
			printf("%d -->", i);
			for (int j=0; j<connComp[i].size(); ++j) {
				printf(" %d", connComp[i][j]);
			}
			printf("\n");
		}
		#endif
		
		if ((connCompN-1)*2 > N) {
			printf("-1\n");
			continue;
		}
		
		if (connCompN == 1) {
			printf("0\n");
			continue;
		}
		
		for (int i=0; i<connCompN; ++i) {
			sort(connComp[i].begin(), connComp[i].end(), connCompare);
		}
		
		#ifdef _DEBUG
		printf("connCompN=%d SORTED\n", connCompN);
		for (int i=0; i<connCompN; ++i) {
			printf("%d -->", i);
			for (int j=0; j<connComp[i].size(); ++j) {
				printf(" %d", connComp[i][j]);
			}
			printf("\n");
		}
		#endif
		
		int ccn = appendMass(connCompN);
		sort(connCompVal, connCompVal+ccn, CCComp);
		
		#ifdef _DEBUG
		printf("CC\n");
		for (int i=0; i<ccn; ++i) {
			printf("(id=%d val=%d)\n", connCompVal[i].connCompNo, connCompVal[i].val);
		}
		#endif
		
		filterOut(ccn, connCompN, N);
		
		#ifdef _DEBUG
		printf("connCompN=%d FILTERED\n", connCompN);
		for (int i=0; i<connCompN; ++i) {
			printf("%d -->", i);
			for (int j=0; j<connComp[i].size(); ++j) {
				printf(" %d", connComp[i][j]);
			}
			printf("\n");
		}
		#endif
		
		int minsum = calcSumMass(connCompN);
		
		printf("%d\n", minsum);
		
	}
	
	return 0;
}
