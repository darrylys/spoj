#include<stdio.h>

int v[44];
unsigned int dp[45][11][4401];

int getdp(int _v, int _p, int x) {
    if (x < 0) return 0;
    else return dp[_v][_p][x];
} 

int min(int a, int b) {
    return (a<b)?a:b;
}

int main() {
    for (int i=0; i<100; ++i) {
        int s;
        for (int j=0; j<44; ++j) {
            scanf("%d", &s);
            v[j] += s;
        }
    }
    
    int X;
    scanf("%d", &X);
    if (X>1000) printf("0\n");
    else {
        dp[1][1][v[0]]=1;
        for (int i=0; i<44; ++i) {
            //dp[1][1][v[i]] = 1;
            dp[i+1][0][0]=1;
        }
        for (int i=2; i<=44; ++i) {
            for (int j=1; j<=min(i,10); ++j) {
                for (int k=0; k<=1000; ++k) {
                    dp[i][j][k] = getdp(i-1, j, k) + getdp(i-1, j-1, k-v[i-1]);
                    //if (k%100==0)printf("[%u,%u,%u]=%u\n", i,j,k,dp[i][j][k]);
                }
            }
        }
        
        unsigned int sum=0;
        for (int i=X; i<=1000; ++i) {
            sum += dp[44][10][i];
        }
        printf("%u\n", sum);
    }
    
}