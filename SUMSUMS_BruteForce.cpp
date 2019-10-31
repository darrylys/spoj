#include<cstdio>
#define ll unsigned long long int
#define MOD 98765431

int main() {
    int n, t, i, j, k, l, res;
    scanf("%d%d", &n, &t);
    int temp[2][n];
    for (i=0;i<n;i++) {
        scanf("%d", &temp[0][i]);
    }

    for (i=0;i<t;i++) {
        for (j=0;j<n;j++) {
            int sum=0;
            for (k=0; k<n; k++) {
                if (j!=k) {
                    sum += temp[0][k];
                    sum %= MOD;
                }
            }
            temp[1][j] = sum;
        }
        for (j=0;j<n;j++) {
            //printf("%10d ", temp[1][j]);
            temp[0][j] = temp[1][j];
        }
        //putchar('\n');
    }
    for (j=0;j<n;j++) {
        printf("%10d\n", temp[0][j]);
    }
    return 0;
}
