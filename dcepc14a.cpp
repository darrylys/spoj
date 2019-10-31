#include <stdio.h>

#define MAXH 301
#define MAXN 100001

int fwickX[MAXH][MAXN];
int arr[MAXN][MAXH];

int getX(int *fenwick, int idx, int maxidx) {
	int sum = 0;
	while (idx > 0) {
		sum += fenwick[idx];
		idx -= (idx & (-idx));
	}
	return sum;
}

int getXY(int xidx, int rval, int maxidx, int maxrval) {
	int sum = 0;
	while (xidx > 0) {
		sum += getX(fwickX[xidx], rval, maxrval);
		xidx -= (xidx & (-xidx));
	}
	return sum;
}

// [0,maxidx)
void updateX(int *fenwick, int idx, int maxidx) {
	while (idx < maxidx) {
		fenwick[idx]++;
		idx += (idx & (-idx));
	}
}

void updateXY(int xidx, int rval, int maxidx, int maxrval) {
	while (xidx < maxidx) {
		updateX(fwickX[xidx], rval, maxrval);
		xidx += (xidx & (-xidx));
	}
}

int main() {
	int R, C;
	scanf("%d %d", &R, &C);
	
	for (int i=0; i<R; ++i) {
		for (int j=0; j<C; ++j) {
			scanf("%d", &arr[i][j]);
		}
	}
	
	int sum = 0;
	for (int i=R-1; i>=0; --i) {
		for (int j=C-1; j>=0; --j) {
			
			updateXY(C-j, arr[i][j], C+1, MAXN);
			sum += getXY(C-j, arr[i][j]-1, C+1, MAXN);
			
		}
	}
	
	printf("%d\n", sum);
	return 0;
}
