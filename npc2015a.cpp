/*
AC 0.29s 2.7M SPOJ

algo:
record the smallest index where character x occurs in string
record the largest index where character x occurs in string
for all character ('A' to 'Z')
let the uninitialized untouched.

for each query:
just compare the smallest vs largest. 
if any of largest or smallest value is uninitialized, print TIDAK
if largest - smallest < 1, print TIDAK else YA

complexity: time O(N + |S|), space: O(1)

*/

#include <stdio.h>

int st[26];
int ed[26];

int main() {
	
	int idx=1;
	
	char in;
	while (((in=getchar()) < 'A') || in > 'Z');
	do {
		if (st[in-'A'] == 0) {
			st[in-'A'] = idx;
		}
		ed[in-'A'] = idx;
		idx++;
	} while ((in=getchar()) >= 'A' && in <= 'Z');
	
	int Q;
	scanf("%d", &Q);
	char X, Y;
	
	while (Q--) {
		while (((X=getchar()) < 'A') || X > 'Z');
		while (((Y=getchar()) < 'A') || Y > 'Z');
		
		if (st[X-'A'] == 0 || ed[Y-'A'] == 0) {
			printf("TIDAK\n");
			
		} else if (st[X-'A'] < ed[Y-'A']) {
			printf("YA\n");
			
		} else {
			printf("TIDAK\n");
			
		}
		
	}
}
