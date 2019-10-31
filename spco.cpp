#include <stdio.h>

#define ull unsigned long long
#define MAXC 65
#define MAXP 25
#define PRIMEIDX 100
//#define DEBUG

// 25
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int primeIdx[PRIMEIDX];

ull C[MAXC][MAXC];
void buildC() {
	for (int i=0; i<MAXC; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j=1; j<i; ++j) {
			C[i][j] = C[i-1][j] + C[i-1][j-1];
		}
	}
}

void buildPrimeIdx() {
	int k = 0;
	int lp = 0;
	for (int i=0; i<PRIMEIDX; ++i) {
		primeIdx[i] = lp;
		if (i == primes[lp]) {
			lp++;
		}
	}
}

int x2b(ull X, char * buf) {
	if (X == 0) { return 0; }
	int len = x2b(X >> 1, buf);
	buf[len] = (X&1);
	return len+1;
}

ull find(ull A) {
	
	char inp[100];
	int len = x2b(A, inp);
	
	#ifdef DEBUG
	printf("A=%llu, len=%d. A[binary]=", A, len);
	for (int i=0; i<len; ++i) {
		putchar(inp[i]+'0');
	}
	printf("\n");
	#endif
	
	int d = 0;
	ull sum = 0;
	for (int i=0; i<len; ++i) {
		if (inp[i]) {
			
			for (int j=primeIdx[d]; (j < MAXP) && (primes[j] - d <= len - i - 1); ++j) {
				sum += C[len-i-1][primes[j]-d];
			}
			
			d++;
		}
	}
	
	return sum;
}

int main() {
	buildC();
	buildPrimeIdx();
	
	int T;
	ull a, b;
	scanf("%d", &T);
	while (T--) {
		scanf("%llu %llu", &a, &b);
		ull la = find(a);
		ull lb = find(b+1);
		
		#ifdef DEBUG
		printf("la=%llu, lb=%llu, lb-la=", la, lb);
		#endif
		
		printf("%llu\n", lb-la);
		
		#ifdef DEBUG
		printf("\n");
		#endif
		
	}
	return 0;
}
