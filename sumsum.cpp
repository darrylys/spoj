#include<stdio.h>

#define MAXN (100010)
#define MAXQ (100010)
#define MOD (59)
#define ll long long
//#define DEBUG

typedef struct _QU {
	int x;
	int idx;
} QU;

int fenwick[32][MAXN];
char bitpos[32][MAXN];
char CMD[] = {'X', 'A', 'O'};
int updateptr = 0;
QU updates[MAXN + MAXQ]; // deferring updates

int getCmd(char cmd) {
	switch (cmd) {
		case 'X': return 0;
		case 'A': return 1;
		case 'O': return 2;
	}
}

ll sumCMD(int cmd, int no1, int no0) {
	switch(cmd) {
		case 0: return (ll)no1*no0;
		case 1: return (ll)no1 * (no1-1) / 2;
		case 2: return (((ll)no1*(no0+no1-1)) + ((ll)no0*no1))/2;
	}
}

// d = 1, +#1, -#0 , d = -1, -#1, +#0
void _add2tree(int * tree, int p, int maxVal, int d) {
	while (p < maxVal) {
		tree[p] += d;
		p += p & (-p);
	}
}
ll get(int * tree, int p) {
	ll sum=0;
	while (p > 0) {
		sum += tree[p];
		p -= (p & (-p));
	}
	return sum;
}
void add2tree(int * tree, char * bitarr, char cmd, int p, int maxVal, char newBit) {
	if (newBit == bitarr[p]) {
		return;
	}
	
	int d = -1;
	if (newBit) d = 1;
	
	_add2tree(tree, p, maxVal, d);
}

// [n1, n2]
ll getInterval(int cmd, int n1, int n2) {
	ll sum=0;
	ll k=1;
	
	int no1 = 0, no0;
	for (int i=0; i<32; ++i) {
		no1 = get(fenwick[i], n2) - get(fenwick[i], n1-1);
		no0 = (n2-n1+1)-no1;
		
		sum += k * sumCMD(cmd, no1, no0);
		k<<=1;
	}
	
	return sum;
}

int main() {
	int N, Q, e;
	scanf("%d %d", &N, &Q);
	
	for (int n=1; n <= N; ++n) {
		scanf("%d", &e);
		updates[updateptr].x = e;
		updates[updateptr].idx = n;
		updateptr++;
	}
	
	int maxe = 0;
	
	while (Q--) {
		int type;
		scanf("%d", &type);
		
		if (type == 1) {
			int x, idx;
			scanf("%d %d", &x, &idx); // idx is 1-based
			updates[updateptr].x = x;
			updates[updateptr].idx = idx;
			updateptr++;
			
		} else {
			char op[5];
			int i1, i2;
			
			scanf("%s %d %d", op, &i1, &i2);
			if (i1 == i2) {
				printf("0\n");
				continue;
			}
			
			int cmd = getCmd(op[0]);
			
			#ifdef DEBUG
			printf("cmd=%d, CMD=%c\n", cmd, CMD[cmd]);
			#endif
			
			// apply updates now
			for (int u=0; u<updateptr; ++u) {
				
				int e = updates[u].x;
				int n = updates[u].idx;
				
				#ifdef DEBUG
				printf("e=%d, n=%d\n", e, n);
				#endif
				
				ll flag = 1;
				for (int i=0; flag <= e || i <= maxe; ++i) {
					add2tree(fenwick[i], bitpos[i], CMD[cmd], n, N+1, (e&flag) != 0);
					bitpos[i][n] = ((e&flag) != 0);
					flag <<= 1;
					
					#ifdef DEBUG
					for (int m=1; m<=N; ++m) {
						printf("[m=%d,#1=%d,cn=%d] ", m, fenwick[i][m], m & (-m));
					}
					printf("\nbitpos[%d]: ", i);
					for (int m=1; m<=N; ++m) {
						printf("%d ", bitpos[i][m]);
					}
					printf("\n");
					#endif
					
					if (maxe < i) {
						maxe = i;
					}
				}
				
			}
			updateptr = 0;
			
			#ifdef DEBUG
			printf("[1..%d]=%lld, [1..%d]=%lld\n", i2, getAll(cmd, i2), i1-1, getAll(cmd, i1-1));
			#endif
			
			printf("%lld\n", getInterval(cmd, i1, i2));
		}
	}
}
