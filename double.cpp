// no branches
// only 1 smallest digit exist!

#include<stdio.h>
#include<string.h>

int gNextState[512]; // [state|carry]
int gMin[2][512];
int gMinLen;
int gMinId;

int findSmallest(int * arr, int len) {
	int minv=10000;
	int mini=0;
	for (int i=0; i<len; ++i) {
		if (arr[i] < minv) {
			minv=arr[i];
			mini=i;
		}
	}
	return mini;
}

int findCycle(int seed, int base) {
	int candId = gMinId^1;
	
	int startState = seed<<1;
	
	if (gNextState[startState] != -1) {
		return 0; // already explored
	}
	
	int t=0;
	int temp[512];
	
	int nv, ns, cc, cd, nc, nd;
	while (1) {
		cd = startState>>1;
		temp[t++] = cd;
		
		cc = startState&1;
		
		nv = cd*2+cc;
		nd = nv%base;
		nc = nv/base;
		
		ns = nc+(nd<<1);
		
		if (gNextState[ns] == -1) {
			gNextState[ns] = startState;
			startState = ns;
			continue;
		}
		
		break;
	}
	
	if (t > gMinLen) {
		return 0;
	}
	
	int si = findSmallest(temp, t-1);
	for (int i=0; i<t-1; ++i) {
		gMin[candId][i] = temp[(si-i+t-1)%(t-1)];
	}
	
	if (t < gMinLen) {
		gMinId = candId;
		gMinLen = t;
		return 0;
	}
	
	for (int i=0; i<t-1; ++i) {
		if (gMin[candId][i] < gMin[gMinId][i]) {
			gMinId = candId;
			break;
		} else if (gMin[candId][i] > gMin[gMinId][i]) {
			break;
		}
	}
	
	return 0;
}

int main() {
	/*for (int b=2; b<=250; ++b) {
		
		memset(gNextState, -1, sizeof(gNextState));
		for (int d=1; d<b; ++d) {
			//printf("seed=%d, base=%d\n", d, b);
			findCycle(d, b);
		}
		
	}*/
	
	int T, B;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &B);
		memset(gNextState, -1, sizeof(gNextState));
		gMinLen = 1000;
		gMinId = 0;
		
		for (int d=1; d<B; ++d) {
			findCycle(d, B);
		}
		for (int i=0; i<gMinLen-1; ++i) {
			printf("%d ", gMin[gMinId][i]);
		}
		putchar('\n');
	}
	
}
