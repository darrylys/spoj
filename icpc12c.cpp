/*
AC, 0.06s, 2.8M SPOJ

algo: ad-hoc

three steps are:
swapping, {0, ...} times
adding prefix {0, ...} times
adding suffix {0, ...} times

any swapping many times means any permutation is allowed

define configuration means #a, b, c, etc.. in a string
for example:
avgn: configuration = {a:1, b:0, c:0, ..., g:1, ..., n:1, ..., v:1, ..., z:0}
abbccd: config = {a:1, b:2, c:2, d:1, ..., z:0}

basically, as long as string A contains the same configuration as string B, we can transform A to B and vice versa
using swapping operation.

let
le = length(encrypted)
lp = length(plaintext)
So, all we need is to find a substring of length lp in encrypted text which configuration is the same as plaintext
if we can find it, YES else NO

*/

#include<stdio.h> 
#include<string.h>

const int MAXN = (100002);

char encry[MAXN];
char plain[MAXN];
int encryConf[26];
int plainConf[26];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		
		scanf("%s", encry);
		scanf("%s", plain);
		
		int le = strlen(encry);
		int lp = strlen(plain);
		
		if (lp > le) {
			printf("NO\n"); continue;
		}
		
		memset(encryConf, 0, sizeof(encryConf));
		memset(plainConf, 0, sizeof(plainConf));
		
		for (int i=0; i<lp; ++i) {
			plainConf[plain[i]-'a']++;
		}
		
		for (int i=0; i<lp; ++i) {
			encryConf[encry[i]-'a']++;
		}
		
		int same=0;
		for (int i=0; i<26; ++i) {
			same += (plainConf[i] == encryConf[i]);
		}
		
		for (int i=lp, di, ii; same != 26 && i<le; ++i) {
			
			di = encry[i-lp]-'a';
			if (encryConf[di] == plainConf[di]) {
				same--;
			}
			encryConf[di]--;
			if (encryConf[di] == plainConf[di]) {
				same++;
			}
			
			
			ii = encry[i]-'a';
			if (encryConf[ii] == plainConf[ii]) {
				same--;
			}
			encryConf[ii]++;
			if (encryConf[ii] == plainConf[ii]) {
				same++;
			}
			
		}
		
		if (same == 26) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
		
	}
}
