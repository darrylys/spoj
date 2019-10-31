/*
AC 0.00s 2.7M spoj

algo:
the bomb here only attacks consecutive undestroyed cells, unlike real bomberman.

bomb 1 == X
..X.....
..X.....
..X.....
XXXXXXXX
..X.....

bomb 2 = Y
..XYYYYY
..X..Y..
..X..Y..
XXXXXXXX
..X.....

notice that the leftmost corner is not destroyed by Y bomb.

whenever a bomb is placed in a field, the field is split to 4, effectively creating 4 separate games
so, check all possible splits of field [W, H] and find the grundy number by DP.

G1X.....
..X..G2.
..X.....
XXXXXXXX
G3X.G4..

grundy number of N separate games played together is the XOR of the grundy number of each individual games
configuration above has grundy number of G1^G2^G3^G4 ; ^=XOR
the configuration above places the bomb at coordinate (row=4, col=3).
for all possible rows and cols, find the grundy number.
and lastly combining all together, find the smallest non-negative number that is not found in any of the
grundy numbers found in all possible configurations above.
@see grundy numbers tutorials in internet

algorithm is at bf.cpp

since there are very few zero grundy numbers, one can just hardcode them in source code!

*/

#include <stdio.h>

int g[] = {2,2,4,4,4,6,6,4,8,12,10,10,12,8}; // 14

int main() {
	int T, M, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &M, &N);
		
		bool win=true;
		for (int i=0; i<14; i+=2) {
			if (M == g[i] && N == g[i+1]) {
				win=false;
				break;
			}
		}
		
		printf("%d\n", win ? 1 : 2);
	}
}
