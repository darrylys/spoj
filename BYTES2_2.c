#include<stdio.h>
#include<string.h>
#define MAX_E 10000000

int t[MAX_E];

int main() {
    int tst, a, b, n, i, max;
    scanf("%d",&tst);
    while(tst--){
        scanf("%d", &n);
        memset(t, 0, MAX_E*4);
        max = -1;
        while(n--) {
            scanf("%d%d", &a, &b);
            for (i=a; i<=b; i++) {
                t[i]++;
                if (t[i] > max) max = t[i];
            }
        }
        printf("%d\n", max);
    }
}
