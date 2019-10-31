//#define DEBUG

#include <stdio.h>

#ifdef DEBUG
#include <time.h>
#endif

#define ll long long
#define MXN 100003
#define MOD 1000000007
//#define MOD 100003

int sumArray[MXN];
int fcompa[MXN];

void build() {
	fcompa[1] = 1;
	for (int i=2; i<MXN; ++i) fcompa[i] = 2;
	
	int pw2, ctmp, now;
	
	for (int i=3, j; i<MXN; ++i) {
		sumArray[i-1] = 0;
		pw2 = 2;
		/*
		for (j=1; j<i; ++j) {
			putchar('\t');
		}
		*/
		for (j=i; j-i+1<i && j<MXN; ++j) {
			sumArray[j] = (pw2 - 1 + MOD);
			if (sumArray[j] >= MOD) sumArray[j] -= MOD;
			
			ctmp = (sumArray[j] - sumArray[j-1] + MOD);
			if (ctmp >= MOD) ctmp -= MOD;
			
			fcompa[j] += ctmp;
			
			if (fcompa[j] >= MOD) {
				fcompa[j] -= MOD;
			}
			
			pw2 = (pw2 << 1);
			if (pw2 >= MOD) pw2 -= MOD;
			
			//printf("i%d,%d\t", sumArray[j], fcompa[j]);
		}
		
		for (; j<MXN; ++j) {
			now = sumArray[j-1] - sumArray[j-i] + MOD;
			if (now >= MOD) now -= MOD;
			
			fcompa[j] += now;
			sumArray[j] = sumArray[j-1] + now;
			
			if (fcompa[j] >= MOD) {
				fcompa[j] -= MOD;
			}
			
			if (sumArray[j] >= MOD) {
				sumArray[j] -= MOD;
			}
			
			//printf("r%d,%d,%d\t", sumArray[j], fcompa[j], now);
		}
		//putchar('\n');
	}
}

int main() {
	#ifdef DEBUG
	const clock_t begin_time = clock();
	#endif
	
	build();
	
	#ifdef DEBUG
	for (int i=1; i<MXN; ++i) {
		printf("%d\n", fcompa[i]);
	}
	
	printf("%lf\n",  float( clock () - begin_time ) /  CLOCKS_PER_SEC);
	#endif
	
	#ifndef DEBUG
	int T, N, c=1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		printf("Case #%d: %d\n", c++, fcompa[N-1]);
	}
	#endif
}


