#include<stdio.h>
#include<string.h>

#define MAXN 210

int dp[MAXN];
char stick[MAXN];

int max(int a, int b) {
    return (a>b) ? a:b;
}

int solve(int n) {
    
    memset(dp, 0, (n+1)*sizeof(int));
    
    int sour, sweet, templ, prev;
    
    for (int i=0; i<=n; ++i) {
        
        //put start split at position i
        
        sour = sweet = 0;
        templ = 0;
        
        //loop for end split
        for (int j=i+1; j<=n; ++j) {
            if (stick[j-1] == '1') {
                sweet++;
            } else {
                sour++;
            }
            
            templ++;
            
            if (sweet > sour) {
                dp[j] = max(dp[j], templ + dp[i]);
            } else {
                dp[j] = max(dp[j-1], dp[j]);
            }
            //printf("%d ", dp[j]);
        }
        //putchar('\n');
        
    }
    
    return dp[n];
}

int main() {
    int test, n;
    scanf("%d", &test);
    
    while (test--) {
        scanf("%d", &n);
        
        scanf("%s", stick);
        
        printf("%d\n", solve(n));
    }
    return 0;
}