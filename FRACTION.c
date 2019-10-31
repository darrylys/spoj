// impl Farey Sequence Generator

#include<stdio.h>
#define N 5000

int farey[N*N][2];

int main() {
    int n, m, testcase, k, i;
    scanf("%d",&testcase);
    while(testcase--) {
        scanf("%d%d",&n,&m);
        farey[0][0] = 0; farey[0][1] = 1; farey[1][0] = 1; farey[1][1] = n;
        i=2;
        do {
            k = (n+farey[i-2][1])/farey[i-1][1];
            farey[i][0] = k*farey[i-1][0] - farey[i-2][0];
            farey[i][1] = k*farey[i-1][1] - farey[i-2][1];
        } while (farey[i++][0] <= n);
        int c;
        while (m--) {
            scanf("%d",&c);
            printf("%d/%d\n", farey[c-1][0], farey[c-1][1]);
        }
    }
    return 0;
}
