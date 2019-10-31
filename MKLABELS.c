#include<stdio.h>
int ans[] = {0,1,1,3,16,125,1296,16807,262144,4782969,100000000};
int main() {
    int n, cntr=1;
    while (scanf("%d",&n) && n)
        printf("Case %d, N = %d, # of different labelings = %d\n", cntr++, n, ans[n]);
    return 0;
}
