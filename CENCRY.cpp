#include<cstdio>
#include<cstring>

char text[50005];
int each[50005];
int cnt[26];

char v[] = {"aeiou"}; //5
char c[] = {"bcdfghjklmnpqrstvwxyz"}; //21

int bs(char* arr, char key, int len) {
	int u=0, v=len;
	while (true) {
		if (u>=v) return u-1;
		else {
			int c = (u+v)/2;
			if (key == arr[c]) return c;
			else if (key > arr[c]) u=c+1;
			else v=c;
		}
	}
}

int main() {
	int t, len, start, res;
	scanf("%d",&t);
	while(t--){
		scanf("%s", text);
		len = strlen(text);
		for (int i=0; i<len; i++) each[i]=0;
		for (int i=0; i<26; i++) cnt[i]=0;
		for (int i=0; i<len; i++) {
			cnt[text[i]-'a']++;
			each[i] = cnt[text[i]-'a'];
		}
		for (int i=0; i<len; i++) {
			if (text[i] == 'a' || text[i] == 'i' || text[i] == 'u' ||
				text[i] == 'e' || text[i] == 'o') {
				start = bs(v, text[i], 5);
				res = (start+5*(each[i]-1))%21;
				putchar(c[res]);
			} else {
				start = bs(c, text[i], 21);
				res = (start+21*(each[i]-1))%5;
				putchar(v[res]);
			}
		}
		putchar('\n');
	}
}
