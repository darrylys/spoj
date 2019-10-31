#include <stdio.h>

#define MX 100005

typedef struct _PAIR {
	int val;
	int idx;
} PAIR;

PAIR stack[MX];
int array[MX];
int lefti[MX];
int righti[MX];

void find(int maxval, int maxidx, int n, int *dest, int dir) {
	int esp = 0;
	PAIR a = {maxval, maxidx};
	stack[esp++] = a;
	
	int i = (maxidx + dir + n) % n;
	
	while (i != maxidx) {
		PAIR top = stack[esp-1];
		if (array[i] > top.val) {
			
			dest[top.idx] = i;
			--esp;
			
		} else {
			PAIR b = {array[i], i};
			stack[esp++] = b;
			i = (i+dir+n)%n;
		}
		
	}
	
	while (1) {
		PAIR top = stack[esp-1];
		if (array[i] > top.val) {
			dest[top.idx] = i;
			--esp;
		} else {
			break;
		}
	}
	
	for (int i=esp-1; i>=0; --i) {
		dest[stack[i].idx] = -2;
	}
}

int main() {
	int T, N, maxval = -1, maxidx = -1;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		maxval = -1;
		maxidx = -1;
		for (int i=0; i<N; ++i) {
			scanf("%d", &array[i]);
			if (array[i] > maxval) {
				maxval = array[i];
				maxidx = i;
			}
		}
		
		find(maxval, maxidx, N, lefti, -1);
		find(maxval, maxidx, N, righti, 1);
		
		for (int i=0; i<N; ++i) {
			printf("%d %d\n", lefti[i]+1, righti[i]+1);
		}
		
	}
	return 0;
}
