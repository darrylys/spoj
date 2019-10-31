#include<stdio.h>
#define NN 86028121

char flag[(NN>>3) + 1];
int prime[5000001];

int main() {
    prime[0] = 2;
    int pntr=1;
    int i, j;
    int off;
    for (i=3;i*i <= NN; i+=2) {
        if (!(flag[i>>3] & (1<<(i&7)))) {
            prime[pntr++] = i;
            off = i << 1;
            for (j=i*i; j<= NN; j+=off) {
				flag[j>>3] |= (1<<(j&7));
			}
        }
    }
    for (;i<= NN; i+=2) {
        if (!(flag[i>>3] & (1<<(i&7)))) {
			prime[pntr++] = i;
		}
    } 
    int q, n; 
    scanf("%d",&q); 
    while(q--){ 
        scanf("%d",&n); 
        printf("%d\n", prime[n-1]); 
    } 
    return 0; 
}

