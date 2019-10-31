#include<cstdio>

#define MAXN 1005

int data[MAXN][MAXN][2];
int dp[MAXN][MAXN];
int arraylocmap[MAXN];

int _min(int a, int b) {
    return (a<=b)?a:b;
}

void processmap(int n) {
    for (int i=1; i<=n; i++) {
        data[i][0][0] = data[i][0][1] = 0;
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<n; j++) {
            int small = data[i][j-1][0];
            int large = data[i][j-1][1];
            
            if (i+j <= n) {
                if (arraylocmap[i+j] < arraylocmap[i]) {
                    large++;
                }
            }
            if (i-j > 0) {
                if (arraylocmap[i-j] < arraylocmap[i]) {
                    small++;
                }
            }
            
            data[i][j][0] = small;
            data[i][j][1] = large;
        }
    }
}

void processdp(int n) {
    for (int i=1;i<=n;i++) {
        dp[i][i] = arraylocmap[i];
    }
    for (int diff = 1; diff < n; diff++) {
        
        for (int min = 1; min+diff <= n; min++) {
            
            int max = min + diff;
            
            dp[max][min] = _min(dp[max-1][min] + (diff+1)*(arraylocmap[max] - data[max][max-min][0]), 
                                        dp[max][min+1] + (diff+1)*(arraylocmap[min] - data[min][max-min][1]));
        }
        //printf("diff = %d ", diff);
    }
    printf("%d\n", dp[n][1]);
}

int main() {
    int t, n, c;
    bool mode;
    scanf("%d",&t);
    while (t--) {
        scanf("%d",&n);
        for (int i=0;i<n;i++) {
            scanf("%d",&c);
            arraylocmap[c] = i+1;
        }
        //printf("1\n");
        processmap(n);
        //printf("2\n");
        processdp(n);
        //printf("3\n");
    }
    return 0;
}