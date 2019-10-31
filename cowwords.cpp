#include<stdio.h>
#include<string.h>

#define MOD (97654321)

int dp[251][251][53];

// available letters
bool avlet[53];

// [ending]
int avlNumber[53];
// [ending][startletter]
int avlPairs[53][201];

int char2int(char x) {
	if (x >= 'A' && x <= 'Z') {
		return x-'A';
	}
	return x-'a'+'Z'-'A'+1;
}

char int2char(int x) {
	if (x <= 'Z'-'A') return x+'A';
	return x-'Z'+'A'-1+'a';
}

int find(int U, int L, int ending) {
//	printf(">>find(%d,%d,%c)\n", U, L, int2char(ending));
	
	if (U < 0 || L < 0) {
		return 0;
	}
	
	if (dp[U][L][ending] != -1) {
		return dp[U][L][ending];
	}
	
	if (U == 0) {
		if (ending <= 'Z'-'A') {
			return dp[U][L][ending] = 0;
		}
		if (L == 1) {
			return dp[U][L][ending] = 1;
		}
	}
	if (L == 0) {
		if (ending > 'Z'-'A') {
			return dp[U][L][ending] = 0;
		}
		if (U == 1) {
			return dp[U][L][ending] = 1;
		}
	}
	
	int sum = 0;
	int nU = U, nL = L;
	if (ending <= 'Z'-'A') {
		nU--;
	} else {
		nL--;
	}
	
//	if (nU < 0 || nL < 0) {
//		return dp[U][L][ending] = sum;
//	}
	
	for (int i=0; i<avlNumber[ending]; ++i) {
		sum += find(nU, nL, avlPairs[ending][i]);
		
//		if (avlPairs[ending][i] <= 'Z'-'A') {
//			sum += find(U-1, L, avlPairs[ending][i]);
//		} else {
//			sum += find(U, L-1, avlPairs[ending][i]);
//		}
		if (sum >= MOD) sum -= MOD;
	}
	
	return dp[U][L][ending] = sum;
}

int main() {
	
	memset(dp, -1, sizeof(dp));
	
	int U, L, P;
	scanf("%d %d %d", &U, &L, &P);
	
	char pair[3];
	for (int i=0; i<P; ++i) {
		scanf("%s", pair);
		
		int end = char2int(pair[1]);
		int beg = char2int(pair[0]);
		avlPairs[end][avlNumber[end]++] = beg;
		avlet[end] = true;
	}
	
	int sum = 0;
	for (int i=0; i<53; ++i) {
		if (avlet[i]) {
			int c = find(U, L, i);
			
			//printf("find(%d,%d,%c)=%d\n", U, L, int2char(i), c);
			
			sum += c;
			if (sum >= MOD) sum -= MOD;
		}
	}
	printf("%d\n", sum);
	return 0;
}
