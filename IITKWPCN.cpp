#include <stdio.h>
int main() {
	int W, B, T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&W,&B);
		printf("%d.000000\n", (B&1));
	}
}