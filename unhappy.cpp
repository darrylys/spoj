#include <stdio.h>
#include <string.h>

#define MXV 1500
#define MXL 20

#define NOSGN (-1)
#define UNHAPPY (-2)
#define FLAGGED (-3)
#define ull unsigned long long

int happydist[MXV];
ull smd[MXL][MXV];
ull fac[MXL];

void buildFac() {
	fac[0] = 1;
	for (int i=1; i<MXL; ++i) {
		fac[i] = fac[i-1] * i;
	}
}

bool isUnHappy(int s) {
	if (happydist[s] == UNHAPPY) {
		return true;
	}
	
	if (happydist[s] >= 0) {
		return false;
	}
	
	printf("ERROR! s=%d\n", s);
	int *x = NULL;
	return *x;
}

// done
int srchappy(int x) {
	if (happydist[x] == FLAGGED) {
		return happydist[x] = UNHAPPY;
	}
	
	if (happydist[x] != NOSGN) {
		return happydist[x];
	}
	
	int tx = x;
	int sum = 0;
	while (tx > 0) {
		int d = tx % 10;
		sum += d*d;
		tx /= 10;
	}
	
	happydist[x] = FLAGGED;
	int res = srchappy(sum);
	if (res == UNHAPPY) {
		return happydist[x] = UNHAPPY;
	} else {
		return happydist[x] = 1 + res;
	}
	
}

// ok
void buildHappyDist() {
	
	memset(happydist, NOSGN, sizeof(happydist));
	
	happydist[0] = UNHAPPY;
	happydist[1] = 0;
	
	for (int i=2; i<MXV; ++i) {
		srchappy(i);
	}
}

// ok (1-5)
void comb(int totalLen, int remLen, int partsum, int startdigit, int digit[10]) {
	
	if (remLen == 0) {
		// add zeros
		
		//ull alc = fac[totalLen];
		ull den = 1;
		for (int d=1; d <= startdigit; ++d) {
			den *= fac[digit[d]];
		}
		
		//alc /= den;
		
		// z = 0
		smd[totalLen][partsum] += fac[totalLen] / den;
		
		// z >= 1
		for (int z = 1; z < MXL - totalLen; ++z) {
			smd[totalLen + z][partsum] += fac[totalLen+z]/den/fac[z]/* - fac[totalLen+z-1]/den/fac[z-1]*/;
		}
	} else {
		
		for (int d=startdigit; d<=9; ++d) {
			
			int newPartSum = partsum + d*d;
			if (newPartSum >= MXV) {
				return;
			}
			
			digit[d]++;
			comb(totalLen, remLen-1, newPartSum, d, digit);
			digit[d]--;
			
		}
		
	}
	
}

void comball() {
	buildFac();
	
	int digit[10];
	memset(digit, 0, sizeof(digit));
	
	for (int i=1; i<MXL; ++i) {
		comb(i, i, 0, 1, digit);
	}
}

int toArray(ull X, char buf[MXL]) {
	if (X == 0) {
		return 0;
	}
	int idx = toArray(X/10, buf);
	buf[idx] = X%10;
	return idx+1;
}

ull find(ull X) {
	char dig[MXL];
	
	int xlen = toArray(X, dig);
	
	ull sum = 0;
	int partdigsum = 0;
	
	// Len < xlen
	// seems OK
	/*for (int i=1; i<xlen; ++i) {
		
		for (int s = MXV-1; s > 0; --s) {
			if (isUnHappy(s)) {
				sum += smd[i][s];
			}
		}
	}*/
	for (int s = MXV-1; s > 0; --s) {
		if (isUnHappy(s)) {
			sum += smd[xlen-1][s];
		}
	}
	
	//printf("sum< = %llu\n", sum);
	
	// Len == xlen
	for (int i=0; i<xlen-1; ++i) {
		
		for (int d=0+(i==0); d<dig[i]; ++d) {
			for (int s = MXV-1; s > 0; --s) {
				
				int ds = s - partdigsum - d*d;
				if (ds >= 0) {
					
					if (isUnHappy(s)) {
						//printf("s=%d, ds=%d, smd[%d][%d]=%llu, sum=%llu\n", s, ds, xlen-i-1, ds, smd[xlen-i-1][ds], sum);
						
						sum += smd[xlen-i-1][ds];
					}
					
				} else {
					break;
				}
				
			}
			
			//printf("i=%d. d=%d, pd=%d, sum=%llu\n", i, d, partdigsum, sum);
		}
		
		partdigsum += dig[i] * dig[i];
		
	}
	
	//printf("sum == = %llu\n", sum);
	
	// Len == xlen in top 10
	// OK
	for (int i=0 + (xlen == 1); i<dig[xlen-1]; ++i) {
		if (isUnHappy(partdigsum + i*i)) {
			//printf("unhappy, i=%d\n", i);
			sum++;
		}
	}
	
	//printf("sum > = %llu\n", sum);
	
	return sum;
	
}

int main() {
	buildHappyDist();
	comball();
	
	for (int i=1; i<MXL; ++i) {
		smd[i][0] = 1;
	}
	
	//smd[0][0] = 1;
	//smd[1][0] = 1;
	
	/*
	for (int L=1; L<MXL; ++L) {
		printf("\n===============================================================================\n");
		for (int s=0; s<MXV; ++s) {
			printf("[%d, %d] => %llu\n", L, s, smd[L][s]);
		}
	}
	*/
	
	
	ull lo, hi;
	while (1) {
		scanf("%llu %llu", &lo, &hi);
		if (lo == 0 && hi == 0) {
			break;
		}
		printf("%llu\n", find(hi+1) - find(lo));
	}
	return 0;
}
