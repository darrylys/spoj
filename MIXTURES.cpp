//implementation: DP-MCM

#include<cstdio>
#define N 105
#define MAX_INT 2147483647
#define MOD 100

int C[N][N];
int F[N][N];

int main() {
    int n;
    while (scanf("%d",&n)!=EOF) {
        for (int i=0;i<n;i++) {
            scanf("%d",&F[i][i]);
            C[i][i] = 0;
        }
        for (int len=1;len<n;len++) {
            int j=len;
            for (int i=0;i<n-len;i++) {
                int min = MAX_INT;
                int temp, tk;
                for (int k=i; k<j; k++) {
                    temp = C[i][k] + C[k+1][j] + F[i][k]*F[k+1][j];
                    if (temp < min) {
                        min = temp;
                        tk = k;
                    }
                }
                C[i][j] = min;
                F[i][j] = (F[i][i] + F[i+1][j])%MOD;
                j++;
            }
        }
        printf("%d\n", C[0][n-1]);
    }
    return 0;
}
