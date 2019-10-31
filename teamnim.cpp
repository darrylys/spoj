/*
AC 0.04s 2.7M SPOJ

algo:
Game theory on Grundy Numbers

There are three possible cases for the team arrangement
1) T1 T2 T1 T2 ...
2) T1 T1 T2 T2 ...
3) T1 T2 T2 T1 ...
with T1 moves first and T2 moves second

case 1:
this is just normal NIM game. if A^B^C == 0, T2 wins else T1 wins. ^ = XOR

case 2:
this is a normal NIM game if two moves Tx Tx is merged to one.
enumerate all the possible moves in 2 turns will result in 2 possibilities.
1) both players take from same pile
	resulting in 2 or more coins taken from one pile
2) players take from different pile
	resulting in 1 or more coins taken from two piles. The number taken doesn't have to be the same

merged to one move as:
a player in a single move may either of the following:
1) take 2 coins or more from one pile
2) take K and L coins from 2 different piles. K >= 1 and L >= 1.

with this modification, the game turned to a normal NIM game.
now, run brute force on all possible configurations for small terms and the losing positions are in the following configurations
1   2   3    | piles
-------------------------
A   A   A    | 
A   A   A+1  | A is even
A   A+1 A    |
A+1 A   A    |

So, if the initial piles configuration is one of above, T2 wins, else T1 wins

case 3:
in this case, T1 moves first followed by the same turns configuration as case 2.
this case can be easily handled by thinking:
	how can T1 change the initial configuration to one of the losing positions in one move?
	move here refer to the original move (case 1), not the merged move in case 2.

if T1 can change the initial configuration to a losing position, then T1 wins, else T2 wins.
*/

#include<stdio.h>
#include<algorithm>

using namespace std;

#define ll long long

const char * TEAM[2] = {
	"Elayne/Nynaeve", "Aviendha/Birgitte"
};

int main() {
	int T;
	ll A, B, C;
	ll X[3];
	
	char p[4][12];
	
	scanf("%d", &T);
	while (T--) {
	
		scanf("%lld %lld %lld", &X[0], &X[1], &X[2]);
		sort(X, X+3);
		A = X[0];
		B = X[1];
		C = X[2];
		
		scanf("%s", p[0]);
		scanf("%s", p[1]);
		scanf("%s", p[2]);
		scanf("%s", p[3]);
		
		int teamorder = 0;
		
		for (int i=0; i<4; ++i) {
			if (p[i][0] == 'E' || p[i][0] == 'N') {
				teamorder += 1;
				
			} else if (p[i][0] == 'A' || p[i][0] == 'B') {
				teamorder += 2;
				
			}
			
			teamorder *= 10;
		}
		
		teamorder /= 10;
		
		if (teamorder == 1212 || teamorder == 2121) {
			int T1 = teamorder/1000;
			int T2 = teamorder%10;
			
			// classic NIM
			if (A ^ B ^ C) {
				printf("%s\n", TEAM[T1-1]);
				
			} else {
				printf("%s\n", TEAM[T2-1]);
				
			}
		
		} else if (teamorder == 1122 || teamorder == 2211) {
			int T1 = teamorder/1000;
			int T2 = teamorder%10;
			
			if ((A == B && B == C && (A%2==0)) || (A == B && C == A+1 && (A%2==0))) {
				printf("%s\n", TEAM[T2-1]);
				
				
			} else {
				printf("%s\n", TEAM[T1-1]);
			}
			
		} else if (teamorder == 1221 || teamorder == 2112) {
			int T1 = teamorder / 1000;
			int T2 = (teamorder%1000) / 100;
			
			if ((A == B && (A%2==0) && C > A) || (A+1 == B && (A%2==0) && C >= A)) {
				
				printf("%s\n", TEAM[T1-1]);
				
			} else {
				
				printf("%s\n", TEAM[T2-1]);
			}
			
		}
	}
}
