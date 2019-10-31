#include <stdio.h>
#include <string.h>

#define MAX2L (1<<18)
#define MAXL 18
#define MODV 29
//#define DEBUG

// encoding to input letter:
// 3 2 1 0
// A L M A
int dp[MAX2L][MAXL];
int ones[MAX2L];

int q[2][MAX2L*MAXL];
char mappedInput[MODV];
int mappedBit[MODV];

int min(int a, int b) {
	return a<b?a:b;
}

int max(int a, int b) {
	return a>b?a:b;
}

int enc(int letterConfig, int cursorPos) {
	return letterConfig * MAXL + cursorPos;
}

void dec(int code, int& letterConfig, int& cursorPos) {
	letterConfig = code / MAXL;
	cursorPos = code % MAXL;
}

// due to reversed encoding, the loop is inverted
void mapLetters(char* input, int len) {
	for (int i=len-1; i>=0; --i) {
		mappedInput[(1<<(len-i-1))%MODV] = input[i];
	}
}

#ifdef DEBUG
void _print10(int x) {
	if (x) {
		_print10(x>>1);
		putchar((x&1)+'0');
	}
}
void print10(int x) {
	if (x==0) putchar('0');
	else _print10(x);
}
void printones() {
	for (int i=0; i<2000; ++i) {
		print10(i);
		printf(" = %d\n", ones[i]);
	}
}
void printmappedbit() {
	for (int i=0; i<MAXL; ++i) {
		printf("%d ==> %d = %d\n", 1<<i, (1<<i)%MODV, mappedBit[(1<<i)%MODV]);
	}
}
#endif

void buildMappedBit() {
	for (int i=0; i<MAXL; ++i) {
		mappedBit[(1<<i)%MODV] = i;
	}
}

void buildOnes() {
	for (int i=0; i<MAX2L; ++i) {
		ones[i] = 0;
		int z = i;
		while (z>0) {
			z -= (z & (-z));
			ones[i]++;
		}
	}
}

int get(char* input, int len) {
	
	int qi = 0;
	int qtop[2] = {0};
	
	int MASK = (1<<len)-1;
	
	#ifdef DEBUG
	printf("MASK="); print10(MASK); printf("\n");
	fflush(stdout);
	#endif
	
	mapLetters(input, len);
	//for (int i=0; i<len; ++i) {
	//	printf("pos(0..n): %d, %c\n", i, mappedInput[(1<<(len-i-1))%MODV]);
	//}
	
	//for (int i=0; i<len; ++i) {
	//	printf("%d\t", (len-i-1));
	//}
	//putchar('\n');
	//for (int i=0; i<len; ++i) {
	//	printf("%c\t", input[i]);
	//}
	//putchar('\n');
	
	dp[0][len-1] = 0;
	q[qi][qtop[qi]++] = -1;
	
	while (qtop[qi] > 0) {
		
		//printf("======================================================================================\nSTART\n");
		
		#ifdef DEBUG
		printf("qi=%d\n", qi);
		fflush(stdout);
		
		if (qtop[qi] >= MAX2L*MAXL || qtop[qi]<0) {
			printf("error, qtop[qi]=%d\n", qtop[qi]);
			fflush(stdout);
		}
		#endif
		
		// read all configs
		for (int i=0; i<qtop[qi]; ++i) {
			
			// read config
			int letterConfig;
			int cursorPos;
			
			int sl;// = mappedInput[(1<<cursorPos)%MODV] - 'A';
			
			// initial state
			if (q[qi][i] == -1) {
				// work
				letterConfig = 0;
				cursorPos = len-1;
				sl = 0;
				
			} else {
				dec(q[qi][i], letterConfig, cursorPos);
				sl = mappedInput[(1<<cursorPos)%MODV] - 'A';
			}
			
			//dec(q[qi][i], letterConfig, cursorPos);
			
			//printf("letterConfig: "); print10(letterConfig); putchar('\n');
			//printf("cursorPos: %d\n", cursorPos);
			
			// compute child
			int mflag = (~letterConfig)&MASK;
			int scost = dp[letterConfig][cursorPos];
			
			#ifdef DEBUG
			printf("mflag: "); print10(mflag); putchar('\n');
			printf("sl=%c\n", (char)(sl+'A'));
			printf("scost=%d\n", scost);
			#endif
			
			//printf("CHILDREN {\n");
			while (mflag > 0) {
				
				//printf("\t{\n");
				// targ pos -> need convert to bit idx.
				int flag = mflag & (-mflag);
				//printf("\t\t"); printf("flag: "); print10(flag); putchar('\n');
				
				// target & source letter
				int tl = mappedInput[flag%MODV] - 'A';
				//printf("\t\ttargetletter: %c\n", (char)(tl+'A'));
				
				// compute cost
				
				int tpos = mappedBit[flag%MODV]+1;
				int sx = max(cursorPos, tpos);
				int sn = min(cursorPos, tpos);
				
				// tcost = alter letter + number of existing letter to pass + fire button
				int tcost = min((sl-tl+26)%26, (tl-sl+26)%26) + ones[ (letterConfig & ((1<<sx)-1)) >> sn ] + 1;
				
				//printf("\t\tsx=%d, sn=%d\n", sx, sn);
				//printf("\t\tones["); print10( (letterConfig & ((1<<sx)-1)) >> sn ); putchar(']'); putchar('\n');
				//printf("\t\ttcost=%d+%d+1=%d\n", min((sl-tl+26)%26, (tl-sl+26)%26), ones[ (letterConfig & ((1<<sx)-1)) >> sn ], tcost);
				
				// put to child
				int childConfig = letterConfig | flag;
				//printf("\t\tchildConfig=%d ; ", childConfig); print10(childConfig); putchar('\n');
				
				int finaltpos = tpos-1;
				if (dp[childConfig][finaltpos] == -1) {
					dp[childConfig][finaltpos] = scost + tcost;
					
					// add to q, after type, the cursor is automatically moved 1 character to the right
					// so, -1 because position is n...210
					q[qi^1][qtop[qi^1]++] = enc(childConfig, finaltpos);
					
				} else {
					dp[childConfig][finaltpos] = min(dp[childConfig][finaltpos], scost + tcost);
				}
				
				mflag -= flag;
				
				//printf("\t}\n");
			}
			
			//printf("}\n");
			
		}
		
		qtop[qi] = 0;
		qi ^= 1;
		
		// compute all children
		
		
		// input for each children 
		
		//printf("END\n======================================================================================\n");
		
	}
	
	int mn = 0;
	for (int i=0; i<MAXL; ++i) {
		if (mn <= 0 || (mn > dp[MASK][i] && dp[MASK][i] != -1)) {
			mn = dp[MASK][i];
		}
	}
	
	return mn;
}

int main() {
	buildMappedBit();
	buildOnes();
	
	//#ifdef DEBUG
	//printones();
	//printmappedbit();
	//#endif
	
	//#ifndef DEBUG
	char input[20];
	
	while(1) {
		scanf("%s", input);
		if (input[0] == '0') {
			break;
		}
		
		int len = strlen(input);
		memset(dp, -1, sizeof(dp));
		
		printf("%d\n", get(input, len));
	}
	//#endif
	
}

