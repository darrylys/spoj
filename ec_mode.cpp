#include <stdio.h>
#include <queue>
#include <math.h>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAXN 1002

typedef struct _PAIR {
	double utpMinCost;
	double opticMinCost;
} PAIR;

int xp[MAXN];
int yp[MAXN];
int parent[MAXN * MAXN];

typedef struct _EDGE {
	int dist;
	int li, ri;
} EDGE;

EDGE edge[MAXN * MAXN];
int eid[MAXN * MAXN];

int find(int a) {
	if (parent[a] != a) {
		parent[a] = find(parent[a]);
	} 
	return parent[a];
}

bool comp(int a, int b) {
	return edge[a].dist < edge[b].dist;
}

PAIR calc(int N, int W, int R, int utpUnitCost, int opticUnitCost) {
	
	//memset(visit, 0, N*sizeof(visit[0]));
	
	//priority_queue<int> pq;
	
	int dx, dy, dist;
	int k = 0;
	
	for (int i=0; i < N-1; ++i) {
		for (int j=i+1; j < N; ++j) {
			dx = xp[i] - xp[j];
			dy = yp[i] - yp[j];
			dist = (dx*dx) + (dy*dy); 
			
			//printf("dist=%d\n", dist);
			
			edge[k].dist = dist;
			//edge[k].dist = hypot(dx, dy);
			edge[k].li = i;
			edge[k].ri = j;
			eid[k] = k;
			k++;
			/*if (pq.size() < N-W) {
				pq.push(dist);
			} else {
				pq.push(dist);
				pq.pop();
			}
			*/
		}
	}
	
	//printf("k=%d\n", k);
	
	sort(eid, eid+k, comp);
	
	PAIR p = {0.0, 0.0};
	
	for (int xi=0, found=0; found < N-W && xi<k; ++xi) {
		
		int i = eid[xi];
		
		//printf("read %d, %lf %lf, edge[i].li=%d edge[i].ri=%d p%d p%d\n", edge[i].dist, p.opticMinCost, p.utpMinCost, edge[i].li, edge[i].ri, find(edge[i].li), find(edge[i].ri));
		
		int pli = find(edge[i].li);
		int pri = find(edge[i].ri);
		//if (!visit[edge[i].li] || !visit[edge[i].ri]) {
		if (pli != pri) {
			
			if (edge[i].dist <= R*R) {
			//if (edge[i].dist <= R) {
				p.utpMinCost += utpUnitCost * sqrt((double)edge[i].dist);
				//p.utpMinCost += utpUnitCost * edge[i].dist;
			} else {
				p.opticMinCost += opticUnitCost * sqrt((double)edge[i].dist);
				//p.opticMinCost += opticUnitCost * edge[i].dist;
			}
			
			
			
			parent[pli] = pri;
			/*visit[edge[i].li] = 1;
			visit[edge[i].ri] = 1;*/
			found++;
			
		}
	}
	
	
	/*while (!pq.empty()) {
		dist = pq.top();
		pq.pop();
		
		printf("ch dist=%d\n", dist);
		
		if (dist <= R*R) {
			//utp
			p.utpMinCost += utpUnitCost * sqrt(dist);
		} else {
			//optic
			p.opticMinCost += opticUnitCost * sqrt(dist);
		}
	}
	*/
	return p;
}

int main() {
	int T;
	int N, R, W, U, V, c=1;
	
	scanf("%d", &T);
	
	while (T--) {
		scanf("%d %d %d %d %d", &N, &R, &W, &U, &V);
		for (int i=0; i<N; ++i) {
			parent[i] = i;
			scanf("%d %d", &xp[i], &yp[i]);
		}
		
		PAIR p = calc(N, W, R, U, V);
		printf("Caso #%d: %.3lf %.3lf\n", c++, p.utpMinCost, p.opticMinCost);
	}
	
	return 0;
}