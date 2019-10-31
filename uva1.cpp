// ad hoc, offline algorithm. 

#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>

#define ll long long
#define MAXN (200010)
#define MAXQ (20010)
#define MAXR (13010)
//#define DEBUG

// coord of houses
int xc[MAXN];
int yc[MAXN];

// distance squared of houses to R1 (_r1) or R2 (_r2), sorted ASC
typedef struct _D2 {
	int d2;
	int idx;
} D2;

typedef struct _Q {
	int R1, R2;
	int idx;
} Q;

bool compD2(D2 a, D2 b) {
	return a.d2 < b.d2;
}

bool compQ(Q a, Q b) {
	if (a.R1 == b.R1) {
		return a.R2 < b.R2;
	}
	return a.R1 < b.R1;
}

D2 d2_r1[MAXN];
//D2 d2_r2[MAXN];
Q query[MAXQ];

int noOfDgh[MAXQ];

int fwick[MAXR];
void _add2Tree(int *arr, int p, int maxp) {
	while (p < maxp) {
		arr[p]++;
		p += (p & (-p));
	}
}
int _get4Tree(int *arr, int p) {
	int sum = 0;
	while (p > 0) {
		sum += arr[p];
		p -= (p & (-p));
	}
	return sum;
}
inline void add2Tree(int p, int maxp) {
	_add2Tree(fwick, p, maxp);
}
inline int getLE(int p) {
	return _get4Tree(fwick, p);
}

void fillHouses(int* xh, int* yh, int N, int rx, int ry, D2* arr) {
	for (int i=0; i<N; ++i) {
		arr[i].d2 = (rx-xh[i])*(rx-xh[i]) + (ry-yh[i])*(ry-yh[i]);
		arr[i].idx = i;
	}
	std::sort(arr, arr+N, compD2);
}

int euclidDist(int x1, int y1, int x2, int y2) {
	return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

int ceilsqrt(int x) {
	//int min_root = (int)( floor( sqrt( min ) ) );
	/*int max_root = */ return (int)( ceil ( sqrt( /*ma*/x ) ) );
	/*
	for (int i=min_root; i<=max_root; ++i) {
		if (i*i == x) {
			return i;
		}
	}
	*/
}

int main() {
	
	int N;
	int r1x, r1y, r2x, r2y, Q, c=1;
	
	while(1) {
		scanf("%d", &N);
		if (N == 0) break;
		
		for (int i=0; i<N; ++i) {
			scanf("%d %d", &xc[i], &yc[i]);
		}
		
		scanf("%d %d %d %d %d", &r1x, &r1y, &r2x, &r2y, &Q);
		
		fillHouses(xc, yc, N, r1x, r1y, d2_r1);
		//fillHouses(xc, yc, N, r2x, r2y, d2_r2);
		
		// put sentinel value
		d2_r1[N].d2 = 14000*14000;
		d2_r1[N].idx = N;
		N++;
		
		#ifdef DEBUG
		printf("sorted on R1\n");
		for (int i=0; i<N; ++i) {
			printf("%d. %d %d\n", i, d2_r1[i].d2, d2_r1[i].idx);
		}
		printf("========\n");
		#endif
		
		for (int i=0; i<Q; ++i) {
			scanf("%d %d", &query[i].R1, &query[i].R2);
			query[i].idx = i;
		}
		
		std::sort(query, query+Q, compQ);
		
		int prevR = 0;
		int nextHouseR1 = 0; // next house to be examined
		for (int i=0; i<Q; ++i) {
			#ifdef DEBUG
			printf("Query: %d %d\n", query[i].R1, query[i].R2);
			#endif
			
			if (query[i].R1 != prevR) {
				
				//loop in R1 until prevR same as query.R1
				int limq = query[i].R1 * query[i].R1;
				for ( ; nextHouseR1 < N && d2_r1[nextHouseR1].d2 <= limq; ++nextHouseR1) {
					
					
					// add to fenwick
					// house: nextHouseR1
					// calc dist to R2, add to fenwick
					int hidx = d2_r1[nextHouseR1].idx;
					int sqDist = euclidDist(xc[hidx], yc[hidx], r2x, r2y);
					int dist2R2 = ceilsqrt(sqDist);
					
					#ifdef DEBUG
					printf("dist2R2=%d\n", dist2R2);
					#endif
					
					add2Tree(dist2R2, MAXR);
					
					#ifdef DEBUG
					printf("processing: {i=%d x=%d y=%d}\n", hidx, xc[hidx], yc[hidx]);
					#endif
				}
				
				prevR = query[i].R1;
			}
			
			int limR2 = query[i].R2;
			int qi = query[i].idx;
			noOfDgh[qi] = getLE(limR2);
		}
		
		printf("Case %d:\n", c++);
		for (int i=0; i<Q; ++i) {
			printf("%d\n", noOfDgh[i]);
		}
	}
	
}
