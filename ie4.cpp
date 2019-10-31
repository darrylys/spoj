#include <stdio.h>
#include <algorithm>

#define ll long long
#define MOD (10007)
#define MAXROCKS (15)
//#define _DEBUG

int fac[MOD];
int invfac[MOD];
int Rockc[MAXROCKS], Rockr[MAXROCKS];
int tRockc[MAXROCKS], tRockr[MAXROCKS];

ll bigmod(int base, int exp, int mod) {
	if (exp == 0 || base == 1) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	half = (half*half)%mod;
	if (exp&1) {
		half = (half*base)%mod;
	}
	return half;
}

ll invmod(int x) {
	return bigmod(x, MOD-2, MOD);
}

void buildFac() {
	fac[0] = 1;
	for (int i=1; i<MOD; ++i) {
		fac[i] = (int)(((ll)fac[i-1] * i)%MOD);
	}
	
	for (int i=0; i<MOD; ++i) {
		invfac[i] = invmod(fac[i]);
	}
	
}

bool comp(int a, int b) {
	if (tRockc[a] == tRockc[b]) {
		return tRockr[a] < tRockr[b];
	} else {
		return tRockc[a] < tRockc[b];
	}
}

// call Combin(N, R) if N and R < MOD
int _C(int N, int R) {
	if (N < R) return 0;
	if (R == N || R == 0) return 1;
	if (R == 1 || R == N-1) return N;
	
	return (int)(((ll)fac[N] * invfac[R] * invfac[N-R])%MOD);
}

// calc Combin(N, R)
int C(int N, int R) {
	
	ll lucas = 1;
	while (N) {
		
		int n0 = N%MOD;
		int r0 = R%MOD;
		lucas = (lucas * _C(n0, r0))%MOD;
		
		N /= MOD;
		R /= MOD;
	}
	
	return (int)(lucas%MOD);
}

//run after canTraverse returns true
// cfid == [START, [ROCKS configuration], TARGET]
int calc(int * rockc, int * rockr, int * cfid, int cfidN) {
	
	// Start = (0,0), Target = (TRow, TCol), already included in rockcr array and cfid array
	
	ll sum = 1;
	
	for (int ii=0; ii<cfidN-1; ++ii) {
		int ci=cfid[ii];
		int ni=cfid[ii+1];
		
		int w = rockc[ni]-rockc[ci];
		int h = rockr[ni]-rockr[ci];
		sum = (sum * C(w + h, w))%MOD;
		
	}
	
	return (int)(sum%MOD);
	
}

// cfid == [START, [ROCKS configuration], TARGET]
bool canTraverse(int * rockc, int * rockr, int * cfid, int cfidN) {
	
	for (int ii=0; ii<cfidN-1; ++ii) {
		int ci=cfid[ii];
		int ni=cfid[ii+1];
		
		if (rockc[ni] < rockc[ci] || rockr[ni] < rockr[ci]) {
			return false;
		}
	}
	
	return true;
}

#ifdef _DEBUG
void _printBinary(int x) {
	if (x) {
		_printBinary(x>>1);
		putchar((x&1)+'0');
	}
}
void printBinary(int x) {
	if (x) _printBinary(x);
	else putchar('0');
}
#endif

int main() {
	buildFac();
	
	int T, R, C, r, c, tR, tC, tr, tc, caseno=1, nrocks;
	int rcid[MAXROCKS];
	
	scanf("%d", &T);
	while (T--) {
		
		scanf("%d %d %d", &R, &C, &nrocks);
		#ifdef _DEBUG
		printf("CASE =======================================================\n");
		printf("R=%d C=%d NROCKS=%d\n", R, C, nrocks);
		#endif
		
		for (int i=0; i<nrocks; ++i) {
			scanf("%d %d", &Rockr[i], &Rockc[i]);
			#ifdef _DEBUG
			printf("read(%d, %d)\n", Rockr[i], Rockc[i]);
			#endif
		}
		
		int zR = R-1, zC = C-1;
		
		if ((2*zR - zC)%3) {
			printf("Case #%d: 0\n", caseno++);
			continue;
		}
		
		tR = (2*zR - zC)/3;
		tC = zR - 2*tR;
		
		// transposed width = tC+1, height = tR+1
		int ti=0;
		for (int i=0; i<nrocks; ++i) {
			Rockr[i]--;
			Rockc[i]--;
			
			#ifdef _DEBUG
			printf("rock (row=%d, col=%d)", Rockr[i], Rockc[i]);
			#endif
			
			if ((2*Rockr[i] - Rockc[i])%3 == 0) {
				tRockr[ti] = (2*Rockr[i] - Rockc[i])/3;
				tRockc[ti] = Rockr[i] - 2*tRockr[ti];
				
				#ifdef _DEBUG
				printf(" --> (row=%d, col=%d)", tRockr[ti], tRockc[ti]);
				#endif
				
				if (tRockc[ti] >= 0 && tRockr[ti] >= 0 && 
					tRockc[ti] <= tC && tRockr[ti] <= tR) {
					
					#ifdef _DEBUG
					putchar('\n');
					#endif
					
					ti++;
				} 
				#ifdef _DEBUG
				else {
					printf(" --> negative col or row! invalid values!\n");
				}
				#endif
			} 
			#ifdef _DEBUG
			else {
				printf("\tfail to transpose\n");
			}
			#endif
		}
		
		// transposing seems correct
		int totalCol = tC+1;
		int totalRow = tR+1;
		
		// add Start
		tRockr[ti] = 0;
		tRockc[ti++] = 0;
		
		// add Target
		tRockr[ti] = tR;
		tRockc[ti++] = tC;
		
		for (int i=0; i<ti; ++i) {
			rcid[i] = i;
		}
		// sort the Rocks (OK)
		std::sort(rcid, rcid+ti, comp);
		
		#ifdef _DEBUG
		printf("(row=%d, col=%d) --> (trow=%d, tcol=%d)\n", zR, zC, tR, tC);
		for (int i=0; i<ti; ++i) {
			printf("rock %d, (row=%d, col=%d)\n", i, tRockr[rcid[i]], tRockc[rcid[i]]);
		}
		#endif
		
		int sign=1;
		int vx, vi, va;
		int cfid[MAXROCKS];
		ll sum = 0;
		
		// ti += 2 (includes START and TARGET) so only ti-2 rocks need to be considered
		for (int i=0; i<(1<<(ti-2)); ++i) {
			
			#ifdef _DEBUG
			printf("%d: ", i); printBinary(i); putchar('\n');
			#endif
			
			vx = i;
			vi = 1;
			va = 1;
			cfid[0] = rcid[0]; // START
			while (vx) {
				if (vx&1) {
					cfid[vi] = rcid[va];
					vi++;
				}
				vx >>= 1;
				va++;
			}
			cfid[vi++] = rcid[ti-1]; // TARGET
			
			#ifdef _DEBUG
			printf("Obtained: \n");
			for (int j=0; j<vi; ++j) {
				printf("rock %d, (row=%d, col=%d)\n", j, tRockr[cfid[j]], tRockc[cfid[j]]);
			}
			printf("]]\n");
			#endif
			
			if (canTraverse(tRockr, tRockc, cfid, vi)) {
				if (vi & 1) {
					sign = MOD-1;
				} else {
					sign = 1;
				}
				
				int c = calc(tRockr, tRockc, cfid, vi);
				#ifdef _DEBUG
				printf("calc=%d\n", c);
				#endif
				
				sum += sign * calc(tRockr, tRockc, cfid, vi);
			}
			
		}
		
		printf("Case #%d: %lld\n", caseno++, sum%MOD);
		
	}
	
	return 0;
}

