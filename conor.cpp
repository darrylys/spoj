#include <stdio.h>

// fenwick, so use index from 1 to 600
// increment all queries!
int fwick[601][601];
int keyArray[601][601];

void update_x(int *tree, int x, int maxX, int k) {
	while (x < maxX) {
		tree[x] ^= k;
		x += (x & (-x));
	}
}

void update(int x, int maxX, int y, int maxY, int k) {
	while (y < maxY) {
		update_x(fwick[y], x, maxX, k);
		y += (y & (-y));
	}
}

int get_x(int *tree, int x, int maxX) {
	int sxor = 0;
	while(x > 0) {
		sxor ^= tree[x];
		x -= (x & (-x));
	}
	return sxor;
}

int getz(int x, int maxX, int y, int maxY) {
	if (x == 0 || y == 0) return 0;
	
	int syor = 0;
	while (y > 0) {
		syor ^= get_x(fwick[y], x, maxX);
		y -= (y & (-y));
	}
	return syor;
}

int get_v(int x1, int y1, int x2, int y2, int maxX, int maxY) {
	
	//printf("[%d,%d]=%d\n[%d,%d]=%d\n[%d,%d]=%d\n[%d,%d]=%d\n",
	//	x2, y2, getz(x2, maxX, y2, maxY),
	//	x2, y1-1, getz(x2, maxX, y1-1, maxY),
	//	x1-1, y2, getz(x1-1, maxX, y2, maxY),
	//	x1-1, y1-1, getz(x1-1, maxX, y1-1, maxY));
	
	return 
		getz(x2, maxX, y2, maxY) ^ getz(x2, maxX, y1-1, maxY) ^ 
		getz(x1-1, maxX, y2, maxY) ^ getz(x1-1, maxX, y1-1, maxY);
	
}

void printKeyArray(int M, int N) {
	for (int y=1; y<=M; ++y) {
		for (int x=1; x<=N; ++x) {
			printf("%d ", keyArray[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}


int main() {
	// M=rows, N=columns
	int M, N, c;
	scanf("%d %d", &M, &N);
	for (int y=1; y<=M; ++y) {
		for (int x=1; x<=N; ++x) {
			scanf("%d", &c);
			update(x, N+1, y, M+1, c);
			keyArray[y][x] = c;
		}
	}
	
	//printKeyArray(M, N);
	
	int Q, r1, r2, c1, c2, rk, cc;
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d", &cc);
		if (cc == 0) {
			// get
			scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
			r1++; c1++; r2++; c2++;
			printf("%d\n", get_v(c1, r1, c2, r2, N+1, M+1));
		} else {
			// update
			scanf("%d %d %d", &r1, &c1, &rk);
			r1++; c1++;
			int xorkey = rk ^ keyArray[r1][c1];
			keyArray[r1][c1] = rk;
			update(c1, N+1, r1, M+1, xorkey);
			
			//printKeyArray(M, N);
		}
	}
	return 0;
}
