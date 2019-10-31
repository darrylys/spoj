#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

#define MAXN 100005
//#define DEBUG

// which articles this author appear at
vector<int> authors[MAXN];

// which authors are registered in this article
vector<int> articles[MAXN];

// erdos number for each author (default = -1)
int autherdos[MAXN];

// flag for already visited articles, default 0
int expandedArticles[MAXN];

// set root nodes at all articles with author = 1
// bfs, rinse & repeat
void build(int A, int N) {
	queue<int> qnode;
	//queue<int> qlevel;
	
	autherdos[1] = 0;
	// add child articles to qnode
	for (int i=authors[1].size()-1, aid; i>=0; --i) {
		aid = authors[1][i];
		qnode.push(aid);
		//qlevel.push(1);
		expandedArticles[aid] = 1;
	}
	
	int erdosfound = 1;
	
	while (!qnode.empty()) {
		int node = qnode.front();
		//int level = qlevel.front();
		int level = expandedArticles[node];
		
		for (int i=articles[node].size()-1, authid; i>=0; --i) {
			
			authid = articles[node][i];
			
			if (autherdos[authid] == -1) {
				autherdos[authid] = level;
				erdosfound++;
				
				if (erdosfound == N) {
					return;
				}
				
				for (int j=authors[authid].size()-1; j>=0; --j) {
					
					int articleID = authors[authid][j];
					if (expandedArticles[articleID] == 0) {
						qnode.push(articleID);
						//qlevel.push(level+1);
						expandedArticles[articleID] = level+1;
					}
				}
			}
		}
		
		qnode.pop();
		//qlevel.pop();
	}
	
}

int main() {
	int A, N, C;
	scanf("%d %d", &A, &N);
	for (int i=0; i<A; ++i) {
		scanf("%d", &C);
		
		for (int j=0, p; j<C; ++j) {
			scanf("%d", &p);
			articles[i].push_back(p);
			authors[p].push_back(i);
		}
	}
	
	memset(autherdos, -1, sizeof(autherdos));
	
	#ifdef DEBUG
	for (int i=0; i<A; ++i) {
		printf("ARTICLE %d\n", i);
		for (int j=articles[i].size()-1; j>=0; --j) {
			printf("%d ", articles[i][j]);
		}
		printf("\n");
	}
	
	for (int i=1; i<=N; ++i) {
		printf("AUTHOR %d\n", i);
		for (int j=authors[i].size()-1; j>=0; --j) {
			printf("%d ", authors[i][j]);
		}
		printf("\n");
	}
	
	for (int i=1; i<=N; ++i) {
		printf("%d ", autherdos[i]);
	}
	printf("\n");
	#endif
	
	build(A, N);
	
	int nvalid = 0;
	int maxval = -1;
	long long sumval = 0;
	
	for (int i=1; i<=N; ++i) {
		
		#ifdef DEBUG
		printf("ERDOS %d >> %d\n", i, autherdos[i]);
		#endif
		
		if (autherdos[i] >= 0) {
			nvalid++;
			if (maxval < autherdos[i]) {
				maxval = autherdos[i];
			}
			sumval += autherdos[i];
		}
	}
	
	printf("%d %d %lld\n", nvalid, maxval, sumval);
	return 0;
}

