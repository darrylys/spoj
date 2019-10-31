/*
AC 0.03s

just precompute the whole thing.
create prime flags first (erathos sieve)
manually check each number from 0 to 10^6 whether they are scary prime or not
put the result in a table.

answer each query in O(1)

*/

#include <stdio.h>

#define MAXN (1000000)
#define STP (1000)

bool flag[MAXN];
int noScary[MAXN];

int buildPrime() {
	
	//primes[0] = 2;
	//int p=1;
	
	for (int i=3; i<MAXN; i+=2) {
		if (!flag[i]) {
			//primes[p++] = i;
			
			if (i < STP) {
				for (int j=i*i, d=i<<1; j<MAXN; j+=d) {
					flag[j] = true;
				}
			}
		}
	}
	
	//return p;
	return 0;
}

void buildScary() {
	
	noScary[0] = noScary[1] = 0;
	noScary[2] = 1;
	noScary[3] = noScary[4] = 2;
	noScary[5] = noScary[6] = 3;
	noScary[7] = noScary[8] = noScary[9] = 4;
	
	int e10 = 10;
	for (int i=10; i < MAXN; ++i) {
		
		if (i/e10 >= 10) {
			e10 *= 10;
		}
		
		if ((i&1) && !flag[i]) { // i == prime
			int trunc = i%e10;
			int ld = trunc / (e10/10);
			
			if (ld) {
				if (noScary[trunc] - noScary[trunc-1] == 1) {
					noScary[i] = noScary[i-1] + 1;
				} else {
					noScary[i] = noScary[i-1];
				}
			} else {
				noScary[i] = noScary[i-1];
			}
			
		} else {
			noScary[i] = noScary[i-1];
		}
		
	}
	
}

int main() {
	buildPrime();
	buildScary();
	
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		
		//printf("isPrime(%d)=%d, ", N, N&1 && !flag[N]);
		printf("%d\n", noScary[N]);
	}
	
}
