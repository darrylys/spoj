#include<stdio.h>
#include<string.h>

#define MAXN (200010)

typedef struct _PAIR {
	bool code;
	int strIdx;
} PAIR;

PAIR stack[MAXN];
char str[MAXN];

inline int max(int a, int b) {
	return (a>b)?a:b;
}

int find(char* in, int len) {
	
	int lenmax = -1;
	int top = 0;
	stack[top].code = false;
	stack[top].strIdx = -1;
	top++;
	
	for (int i=0; i<len; ++i) {
		
		// push to stack
		stack[top].code = (in[i] == '1');
		stack[top].strIdx = i;
		top++;
		
		// read top 3
		while (top >= 3 && !stack[top-1].code && !stack[top-2].code && stack[top-3].code && stack[top-3].strIdx >= 0) {
			top -= 3;
		}
		lenmax = max(lenmax, i - stack[top-1].strIdx);
	}
	
	return lenmax;
}

int main() {
	int T, c=1;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", str);
		printf("Case %d: %d\n", c++, find(str, strlen(str)));
	}
	return 0;
}

