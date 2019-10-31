/*
AC 2.26s 8.4M SPOJ

algo:
basically, enumerate all possible min-max character pair since there are only 26 possible characters
the (maximum, minimum) character pair will be one of all possible pairs.

for each possible pair
construct a new string which is a subsequence of the original string and consists of only
characters in the pair. So, if a pair is (a,b), take only a,b characters from the original string
and create a new smaller string

string: aanananabbabbannaban
pair (a,b): aaaaabbabbaaba (remove all n)

now, simply construct a KADANE-like algorithm (not to be confused to KANADE)
https://en.wikipedia.org/wiki/Maximum_subarray_problem
to calculate the maximum difference

for example: pair = (a,b)
set maximum character = a, minimum character = b
now, simply scan the whole string like in KADANE algorithm
in KADANE, it is values, not characters. Replace the maximum character with 1 and minimum character with -1
and proceed (ALMOST) like KADANE.

some pointers:
	the algorithm needs to take into account that the minimum occurence must be at least 1. This is slightly different
	to the original KADANE where it does not have such restriction.
	as such: string aaaaaaaaaaa, which is replaced to 11111111111, has maximum difference of 0.
	while in original KADANE, 11111111111 has maximum subarray sum of 11.
	
	and string aaaaba which is replaced to 1 1 1 1 -1 1 has maximum subarray of 4, the same as
	KADANE counterpart

	Also remember to take care when dealing with strings like:
	aabbbbaaaaaaaaa, replaced to 1 1 -1 -1 -1 -1 1 1 1 1 1 1 1 1 1
	KADANE algorithm will only process the last aaaaaaaaa, but remember to also take the last 'b', resulting in baaaaaaaaa
	so, the maximum difference is 8, not 9 (original KADANE)
	
Time Complexity: O(104 * N)
assuming equal distribution between letters in string of length N,
each letter will get (1/26) portion of N resulting in N/26 for each letter.
two letter will get a N/13 combined length.
the algorithm is run with (26 * 26 * 2 * N/13) number of operations.

Space complexity: O(N)

*/

#include<stdio.h>

//#define _DEBUG

const int MAXN = 1000001;

char text[MAXN];
char stext[MAXN];
int first[27];
int next[MAXN];

int max(int a, int b) {
	return a>b?a:b;
}

int findMax(char * str, int len, int maxletter, int minletter, int lastmin) {
	
	int maxdiff=-1;
	
	int mine=0;
	int maxe=0;
	
	for (int i=0; i<len; ++i) {
		if (str[i] == maxletter) {
			maxe++;
		} else {
			mine++;
		}
		
		if (mine >= 1) {
			if (maxdiff < maxe - mine) {
				maxdiff = maxe - mine;
			}
			
			if (maxe - mine < 0) {
				if (i == lastmin) {
					mine = 1;
				} else {
					mine = 0;
				}
				
				maxe = 0;
			}
		}
	}
	
	return maxdiff;
	
}

int main() {
	int N;
	scanf("%d", &N);
	scanf("%s", text);
	
	//printf("read=[%s]\n", text);
	
	for (int i=0; i<N; ++i) {
		text[i] -= 'a';
	}
	
	//printf("1\n");
	
	for (int i=0; i<26; ++i) {
		first[i] = -1;
	}
	
	//printf("2\n");
	
	for (int i=N-1; i>=0; --i) {
		next[i] = first[text[i]];
		first[text[i]] = i;
	}
	
	#ifdef _DEBUG
	for (int i=0; i<N; ++i) {
		printf("%d\t", i);
	}
	printf("\n");
	
	for (int i=0; i<N; ++i) {
		printf("%d\t", next[i]);
	}
	printf("\n");
	#endif
	
	int ans = 0;
	
	for (int i=0; i<26; ++i) {
		for (int j=i+1; j<26; ++j) {
			// find the string consists of char i and j
			
			int ai=first[i];
			int aj=first[j];
			
			if (ai >= 0 && aj >= 0) {
				
				int sn=0;
				int lastai, lastaj;
				
				while (ai >= 0 || aj >= 0) {
					
					while (ai >= 0 && (ai < aj || aj == -1)) {
						lastai = sn;
						stext[sn++] = text[ai];
						ai = next[ai];
					}
					
					while (aj >= 0 && (aj < ai || ai == -1)) {
						lastaj = sn;
						stext[sn++] = text[aj];
						aj = next[aj];
					}
					
				}
				
				#ifdef _DEBUG
				for (int k=0; k<sn; ++k) {
					putchar(stext[k]+'a');
				}
				putchar('\n');
				#endif
				
				// first pass:, set MAX = i, MIN = j, diff = i-j
				int me = findMax(stext, sn, i, j, lastaj);
				
				// second pass:, set MAX = j, MIN = i, diff = j-i
				int me2 = findMax(stext, sn, j, i, lastai);
				
				#ifdef _DEBUG
				printf("[max=%c --> min=%c] = %d\n", i+'a', j+'a', me);
				printf("[max=%c --> min=%c] = %d\n", j+'a', i+'a', me2);
				#endif
				
				ans = max(ans, max(me, me2));
			}
			
		}
	}
	
	printf("%d\n", ans);
}
