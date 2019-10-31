#include<stdio.h>

int dp[101][101];
int field[101][101];

int max(int a, int b){return (a>=b)?a:b;}

int main() {
    int t,r,c,i,j,k,mx;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&r,&c);
        for(i=0;i<r;i++){
            for(j=0;j<c;j++){
                scanf("%d",&field[i][j]);
            }
        }
        for(i=0;i<c;i++) dp[0][i] = field[0][i];
        for(i=1;i<r;i++) {
            dp[i][0] = max(dp[i-1][0],dp[i-1][1]) + field[i][0];
            for (j=1; j<c-1; j++) {
                dp[i][j] = max(dp[i-1][j-1], max(dp[i-1][j], dp[i-1][j+1]))+field[i][j];
            }
            dp[i][c-1] = max(dp[i-1][c-1],dp[i-1][c-2]) + field[i][c-1];
        }
        mx = -1;
        for (i=0;i<c;i++) {
            if (dp[r-1][i] > mx) mx = dp[r-1][i];
        }
        printf("%d\n", mx);
    }
}
