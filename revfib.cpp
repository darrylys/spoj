#include <stdio.h>
#include <string.h>
#include <math.h>

// 100000th fib is ~21000 digits, kept in ~2100 elem array
#define MAXN 2400
#define TMAX 3567713
#define XMAX 100000
#define ll long long
#define DIG (1000000000)

// 0 == least significant digit, 1 == most signf digit
int gbuf[3][MAXN];
int glx[3];
int e10[10];
const double LOG10 = log(10);

int max(int a, int b) {
	return a>b ? a:b;
}

// trie
typedef struct _NODE {
	int child[10];
} NODE;

// needs to build trie structure here or some stuff.
int firstN[TMAX];
NODE node[TMAX];

// 0 == root node (occupied!)
int nodeptr = 1;

void buildE10() {
	e10[0] = 1;
	for (int i=1; i<10; ++i) {
		e10[i] = e10[i-1] * 10;
	}
}

int add(int *a, int lena, int *b, int lenb, int *res, int lenres) {
	// c <- a + b, returns c.len
	
	int maxl = max(lena, lenb);
	int carry = 0;
	int temp;
	
	int lenc = 0;
	
	for (int i=0; i<maxl; ++i) {
		temp = a[i] + b[i] + carry;
		
		res[i] = temp % DIG;
		carry = temp / DIG;
	}
	
	lenc = maxl;
	
	if (carry != 0) {
		res[maxl] = carry;
		lenc++;
	}
	
	return lenc;
}

void printTabs(int indent) {
	while(indent--)putchar('\t');
}

void printTrie(int currpos, int indent, int xi) {
	
	printTabs(indent);
	printf("(%d %d %d){\n", currpos, firstN[currpos], xi);
	
	for (int i=0; i<10; ++i) {
		
		if (node[currpos].child[i]) {
			printTrie(node[currpos].child[i], indent+1, i);
		}
	}
	
	printTabs(indent);
	printf("}\n");
	
}

int appendTrie(int digit, int currpos, int fibno) {
	if (node[currpos].child[digit] == 0) {
		node[currpos].child[digit] = nodeptr;
		firstN[nodeptr] = fibno;
		
		nodeptr++;
	}
	
	return node[currpos].child[digit];
}

int find(char *buf, int len) {
	
	int lp = 0;
	int currpos = 0;
	while (lp < len) {
		
		if (node[currpos].child[buf[lp]-'0'] == 0) {
			return -1;
		}
		
		currpos = node[currpos].child[buf[lp]-'0'];
		lp++;
		
	}
	
	return firstN[currpos];
	
}

void printFibo(int *buf, int len, int fibidx) {
	printf("FIB %d: ", fibidx);
	for (int i=len-1; i>=0; --i) {
		printf("%d ", buf[i]);
	}
	putchar('\n');
}

int build() {
	memset(firstN, -1, sizeof(firstN));
	buildE10();
	
	gbuf[0][0] = 1;
	glx[0] = 1;
	
	gbuf[1][0] = 1;
	glx[1] = 1;
	
	//printf("appendTries\n");
	
	appendTrie(1, 0, 0);
	appendTrie(1, 0, 1);
	
	int ai = 0, bi = 1, ci = 2;
	
	//printFibo(gbuf[0], glx[0], 0);
	//printFibo(gbuf[1], glx[1], 1);
	
	for (int i=2; i<XMAX; ++i) {
		ci = i % 3;
		bi = (i+2)%3;
		ai = (i+1)%3;
		
		glx[ci] = add(gbuf[ai], glx[ai], gbuf[bi], glx[bi], gbuf[ci], glx[ci]);
		//printFibo(gbuf[ci], glx[ci], i);
		
		// 1st digit
		int fe = (int)floor( log(gbuf[ci][glx[ci]-1]) / LOG10 );
		int processedDigit = 0;
		bool done = false;
		int currpos = 0;
		
		for (int k=glx[ci]-1; k>=0 && !done; --k) {
			
			int sti = gbuf[ci][k];
			for (int x = fe; x>=0 && !done; --x) {
				int digit = sti / e10[x];
				
				currpos = appendTrie(digit, currpos, i);
				
				processedDigit++;
				
				sti %= e10[x];
				
				if (processedDigit >= 40) {
					done = true;
				}
			}
			
			fe = 8;
		}
	}
	
	return nodeptr;
}

int main() {
	int r = build();
	//printf("final nodeptr=%d\n", nodeptr);
	
	//printTrie(0, 0, -1);
	
	if (r == -1) {
		printf("ERROR, nodeptr >= TMAX\n");
		return 0;
	}
	int T, c=1, Nl;
	char N[45];
	
	scanf("%d", &T);
	while (T--) {
		scanf("%s", N);
		Nl = strlen(N);
		printf("Case #%d: %d\n", c++, find(N, Nl));
	}
	
	return 0;
}
