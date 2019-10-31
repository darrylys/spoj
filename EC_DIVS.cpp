#include <stdio.h>
#include <string.h>

#define MAXN 10005

//#define DEBUG

int sgt[MAXN * 4];
int xID[MAXN];
int noOfItems[MAXN];
char flag[MAXN];
int divisors[MAXN][2][50];

void reset() {
	memset(sgt, 0, sizeof(sgt));
	memset(noOfItems, 0, sizeof(noOfItems));
}

#ifdef DEBUG
void printSpace(int in) {
	while(in--)putchar(' ');
}
void _printList(int root, int a, int b, int in) {
	printSpace(in);
	printf("[%d %d %d {%d}]\n", root, a, b, sgt[root]);
	if (a != b-1) {
		_printList(root*2, a, (a+b)/2, in+4);
		_printList(root*2+1, (a+b)/2, b, in+4);
	}
}
void printList() {
	_printList(1, 1, 10001, 0);
}
#endif

void buildList(int root, int a, int b) {
	if (a == b-1) {
		xID[a] = root;
		/*if (root >= MAXN*4) {
			printf("ROOT DANGER!, root=%d, a=%d, b=%d\n", root, a, b);
		}*/
	} else {
		int lh = root<<1;
		int rh = lh + 1;
		buildList(lh, a, (a+b)/2);
		buildList(rh, (a+b)/2, b);
	}
}

int gcd(int a, int b) {
	int c;
	while (b > 0) {
		c = a%b;
		a = b;
		b = c;
	}
	return a;
}

void buildPrime() {
	flag[2] = 1;
	int i;
	for (i=3; i*i <= 10000; i += 2) {
		if (!flag[i]) {
			flag[i] = 1;
			
			for (int j=i*i; j<=10000; j+= 2*i) {
				flag[j] = -1;
			}
		}
	}
	
	for (; i<=10000; i+=2) {
		if (!flag[i]) {
			flag[i] = 1;
		}
	}
}

bool isPrime(int x) {
	return (x == 2) || ((x&1) && flag[x] == 1);
}

void buildDivisors() {
	
	int clf;
	int rgf;
	for (int i=1; i<=10000; ++i) {
		clf = 1;
		rgf = 1;
		for (int j=1; j*j <= i; ++j) {
			if (i%j == 0) {
				if (!isPrime(j)) divisors[i][0][clf++] = j;
				if (!isPrime(i/j) && j != i/j) divisors[i][1][rgf++] = i/j;
			}
		}
		
		divisors[i][0][0] = clf;
		divisors[i][1][0] = rgf;
		//printf("%d %d\n", clf, rgf);
	}
}

void updateElem(int x, int newValue) {
	int root = xID[x];
		
	sgt[root] = newValue;
	root >>= 1;
	
	while (root) {
		int lh = root<<1;
		int rh = lh+1;
		
		if (sgt[lh] == 0) sgt[root] = sgt[rh];
		else if (sgt[rh] == 0) sgt[root] = sgt[lh];
		else sgt[root] = gcd(sgt[lh], sgt[rh]);
		
		root >>= 1;
	}
}

void removeElem(int x) {
	noOfItems[x]--;
	
	if (noOfItems[x] == 0) {
		updateElem(x, 0);
	}
}

void insertElem(int x) {
	noOfItems[x]++;
	
	if (noOfItems[x] == 1) {
		updateElem(x, x);
	}
}

int main() {
	buildList(1, 1, 10001);
	buildPrime();
	buildDivisors();
	
	int T, N, X;
	char cmd[5], mode[5];
	scanf("%d", &T);
	while(T--){
		reset();
		
		scanf("%d", &N);
		while (N--) {
			scanf("%s", cmd);
			
			#ifdef DEBUG
			printf("CMD=%s\n", cmd);
			#endif
			
			if (cmd[0] == 'C') {
				X = sgt[1];
				
				if (X) {
					for (int i=1; i < divisors[X][0][0]; ++i) {
						printf("%d ", divisors[X][0][i]);
					}
					for (int i=divisors[X][1][0]-1; i > 0; --i) {
						printf("%d ", divisors[X][1][i]);
					}
					printf("\n");
				} else {
					printf("-1\n");
				}
			} else {
				scanf("%s %d", mode, &X);
				
				if (mode[0] == 'A') {
					insertElem(X);
				} else {
					removeElem(X);
				}
				#ifdef DEBUG
				printf("PRINTLIST: mode=%s, X=%d\n", mode, X);
				printList();
				#endif
			}
		}
	}
	return 0;
}
