#include <stdio.h>

#define BIG (1000000000)

// rooted at (0 = 4, 1 = 5), (x = i), ( 0=4 / 1=5 )
int tbl[2][15][2];
int sum[2][15];

void buildroot(int root) {
	root = root&1;
	
	tbl[root][0][root]++;
	
	//tbl[root][0][0] = !root;
	//tbl[root][0][1] = !root;
	sum[root][0] = tbl[root][0][0] + tbl[root][0][1];
	
	//printf("tbl[%d][%d][%d]=%d tbl[%d][%d][%d]=%d sum=%d\n", root, 0, 0, tbl[root][0][0], root, 0, 1, tbl[root][0][1], sum[root][0]);
	
	for (int i=1; ; ++i) {
		tbl[root][i][0] = tbl[root][i-1][0] + tbl[root][i-1][1];
		tbl[root][i][1] = 4*tbl[root][i-1][0] + 5*tbl[root][i-1][1];
		sum[root][i] = tbl[root][i][0] + tbl[root][i][1];
		
		//printf("tbl[%d][%d][%d]=%d tbl[%d][%d][%d]=%d sum=%d\n", root, i, 0, tbl[root][i][0], root, i, 1, tbl[root][i][1], sum[root][i]);
		
		if (sum[root][i] > BIG) {
			break;
		}
	}
}

void build() {
	
	buildroot(4);
	
	//printf("===============================\n");
	buildroot(5);
	
	//printf("===============================\n");
}

inline int t(int x) {
	return x&1;
}

int getn(int n) {
	
	int xn = n;
	int sn = 0;
	int level = 0;
	//printf("xn=%d\n", xn);
	
	for (int i=0; ; ++i) {
		
		sn = sum[0][i];//tbl[0][i][0] + tbl[0][i][1];
		
		if (sn > xn) {
			level = i;
			break;
		} else {
			xn -= sn;
		}
		
	}
	
	printf("level=%d, xn=%d\n", level, xn);
	
	int root[] = {4, 0, 0, 0, 0, 0, 0};
	int pr = 0;
	bool found = false;
	
	while (!found) {
		
		for (int i=0; root[i]; ++i) {
			if (xn == 0 && level == 0) {
				//printf("finished! root[%d]=%d\n", i, root[i]);
				
				// found
				pr = i;
				found = true;
				break;
			} else {
				
				//printf("xn=%d, level=%d, sum[%d][%d]=%d, root[%d]=%d\n", xn, level, t(root[i]), level, sum[t(root[i])][level], i, root[i]);
				
				if (xn >= sum[t(root[i])][level]) {
					//printf("next sibling\n");
					
					// cont to next sibling
					xn -= sum[t(root[i])][level];
					
				} else {
					//printf("break down node. root[%d]=%d\n", i, root[i]);
					
					// break down node
					level--;
					int s = root[i];
					
					root[0] = root[1] = root[2] = root[3] = 5;
					if (s == 4) {
						root[4] = 4;
						root[5] = 0;
					} else {
						root[4] = 5;
						root[5] = 4;
					}
					
					break;
				}
			}
		}
		
	}
	
	return root[pr];
}

int main() {
	build();
	
	int T, N;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		printf("%d\n",getn(N));
	}
	
}
