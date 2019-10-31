#include<stdio.h>

#define MAXN 104
#define L 0
#define M 1

int db[MAXN][MAXN][2];
int dp[MAXN][MAXN][2];
int array[MAXN];

void make_db(int n) {
    int x; //Linggates last job in optimal split
    int tl, tm;
    
    for (int i=0; i<n; ++i) {
        
        db[i][i][L] = array[i];
        db[i][i][M] = 0;
        x = i;
        
        for (int j=i+1; j<n; ++j) {
            //try to take the job
            tm = db[i][j-1][M] + array[j];
            tl = db[i][j-1][L];
            
            while (tm >= tl) {
                ++x;
                tm -= array[x];
                tl += array[x];
            }
            
            db[i][j][L] = tl;
            db[i][j][M] = tm;
        }
    }
}

int solve(int n) {
    for (int i=0; i<n; ++i) {
        dp[0][i][L] = db[0][i][L];
        dp[0][i][M] = db[0][i][M];
    }
    
    int max, maxr;
    
    for (int i=1; i<n; ++i) {
        
        max = -1;
        for (int j=0; j<i; ++j) {
            if (max < dp[j][i-1][M]) {
                max = dp[j][i-1][M];
                maxr = j;
            }
        }
        
        for (int j=i; j<n; ++j) {
            dp[i][j][L] = dp[maxr][i-1][L] + db[i][j][L];
            dp[i][j][M] = dp[maxr][i-1][M] + db[i][j][M];
        }
    }
    
    max = -1, maxr;
    for (int i=0; i<n; ++i) {
        if (max < dp[i][n-1][M]) {
            max = dp[i][n-1][M];
            maxr = i;
        }
    }
    return maxr;
}

void print_db(int n) {
    for (int i=0; i<n; ++i) {
        for (int j=0; j<i; ++j) {
            printf("[---,---] ");
        }
        for (int j=i; j<n; ++j) {
            printf("[%3d,%3d] ", db[i][j][L], db[i][j][M]);
        }
        putchar('\n');
    }
}

int main() {
    int test, n, r;
    scanf("%d", &test);
    
    while (test--) {
        scanf("%d", &n);
        if (n) {
            for (int i=0; i<n; ++i) {
                scanf("%d", &array[i]);
            }
            
            
            make_db(n);
            r = solve(n);
            
            printf("%d %d\n", dp[r][n-1][L], dp[r][n-1][M]);
        } else {
            printf("0 0\n");
        }
    }
    return 0;
}