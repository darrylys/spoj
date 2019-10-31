/*
AC 0.02s 2.7M SPOJ

algo:
see http://profutonium.blogspot.sg/p/spoj-updates.html

sort the coordinates in x , then y
group the smallest x, then smallest y.
notice that there are even number of points with the same x.
to make those points valid, the smallest y point and next smallest y point in same x must be connected.
this marks the building vertical walls.

sort the coordinates again in y, then x
repeat the process
this marks the building horizontal walls.

the difficulty right now is:
	given a point, find the direction he should be walking.

find the point with smallest x, then smallest y.
from this point, he must always walk north for counterclockwise movement.
no other direction is possible. See the following illustration (point P):
   
 O  | Inside
 u  | Building
 t  P_____.....
 s   
 i d e

now, it is simply just traversing the building walls.
record the direction he is walking from this point.

to support given point, simply start printing the result from
the given point and print until all N directions are displayed.

Time / space complexity: O(T * N lg N)
*/

#include<stdio.h>
#include<algorithm>

//#define _DEBUG

using namespace std;

const int MAXN = 1005;

typedef struct _P {
	int x, y;
	int p[2];
} P;

P pt[MAXN];
int ptid[MAXN];
char res[MAXN];

bool compxy(int a, int b) {
	if (pt[a].x == pt[b].x) {
		return pt[a].y < pt[b].y;
	}
	return pt[a].x < pt[b].x;
}

bool compyx(int a, int b) {
	if (pt[a].y == pt[b].y) {
		return pt[a].x < pt[b].x;
	}
	return pt[a].y < pt[b].y;
}

int solve(int npoint, char * buf) {
	
	sort(ptid, ptid+npoint, compxy);
	
	#ifdef _DEBUG
	printf("sortxy\n");
	#endif
	
	for (int i=0; i<npoint; i+=2) {
		int cid = ptid[i];
		int nid = ptid[i+1];
		
		pt[cid].p[0] = nid;
		pt[nid].p[0] = cid;
		
		#ifdef _DEBUG
		printf("%d => (%d,%d)\n", cid, pt[cid].x, pt[cid].y);
		printf("%d => (%d,%d)\n", nid, pt[nid].x, pt[nid].y);
		#endif
	}
	
	int bptnID = ptid[0];
	
	sort(ptid, ptid+npoint, compyx);
	
	#ifdef _DEBUG
	printf("\nsortyx\n");
	#endif
	
	for (int i=0; i<npoint; i+=2) {
		int cid = ptid[i];
		int nid = ptid[i+1];
		
		pt[cid].p[1] = nid;
		pt[nid].p[1] = cid;
		
		#ifdef _DEBUG
		printf("%d => (%d,%d)\n", cid, pt[cid].x, pt[cid].y);
		printf("%d => (%d,%d)\n", nid, pt[nid].x, pt[nid].y);
		#endif
		
	}
	
	int cid = bptnID;
	int dir = 0;
	int stp = 0;
	
	for (int i=0; i<npoint; ++i) {
		
		int nid = pt[cid].p[dir];
		
		if (dir == 0) {
			if (pt[nid].y > pt[cid].y) {
				// upward
				buf[i] = 'N';
			} else {
				// downward
				buf[i] = 'S';
			}
		} else {
			if (pt[nid].x > pt[cid].x) {
				// right
				buf[i] = 'E';
			} else {
				// left
				buf[i] = 'W';
			}
		}
		
		if (cid == 0) {
			stp = i;
		}
		
		dir ^= 1;
		cid = nid;
	}
	
	return stp;
}

int main() {
	
	int N, x, y;
	
	while (scanf("%d", &N) && N) {
		for (int i=0; i<N; ++i) {
			scanf("%d %d", &pt[i].x, &pt[i].y);
			ptid[i] = i;
		}
		
		int st = solve(N, res);
		for (int i=0; i<N; ++i) {
			putchar(res[(i+st)%N]);
		}
		putchar('\n');
	}
	
}
