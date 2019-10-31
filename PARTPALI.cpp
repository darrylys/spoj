#include<stdio.h>
#include<string.h>

#define MAXS 25
#define MAXX 1005

unsigned int dp[MAXS][MAXX];

int big_mod(int base, int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base%mod;
    
    int a = big_mod(base, exp>>1, mod);
    
    if (exp&1) {
        return (a*a*base)%mod;
    } else {
        return (a*a)%mod;
    }
}

void init(int m) {
    memset(dp, 0, sizeof(dp));
    
    for (int j=0; j<=9; ++j) {
        dp[1][j%m]++;
    }
    
    for (int j=0; j<100; j += 11) {
        dp[2][j%m]++;
    }
}

int run(int m, int s) {
    
    int x;
    if (s > 2) {
        for (int k=3; k<s; ++k) {
            
            for (int d=0; d<=9; ++d) {
                x = (d * big_mod(10, k-1, m) + d)%m;
                //printf("k=%d d=%d x=%d\n", k, d, x);
                for (int h=0; h<m; ++h) {
                    dp[k][(x + 10*h)%m] += dp[k-2][h];
                    //if ((x+10*h)%m == 0) {
                    //    printf("k=%d d=%d x=%d h=%d\n", k, d, x, h);
                    //}
                    
                }
                
            }
            /*
            for (int i=0; i<m; ++i) {
                printf("k=%d => i=%d, dp=%d\n", k, i, dp[k][m][i]);
            }
            putchar('\n');*/
        }
        for (int d=1; d<=9; ++d) {
            x = (d * big_mod(10, s-1, m) + d)%m;
            //printf("k=%d d=%d x=%d\n", k, d, x);
            for (int h=0; h<m; ++h) {
                dp[s][(x + 10*h)%m] += dp[s-2][h];
                //if ((x+10*h)%m == 0) {
                //    printf("k=%d d=%d x=%d h=%d\n", k, d, x, h);
                //}
                
            }
        }
    }
    if (s == 1 || s == 2) return dp[s][0]-1;
    else return dp[s][0];
}

int main() {
    //init();
    
    int t, m, s;
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d %d", &m, &s);
        init(m);
        printf("%u\n", run(m, s));
        
        /*
        for (int i=0; i<m; ++i) {
            printf("k=%d => i=%d, dp=%d\n", 8, i, dp[8][i]);
        }
        putchar('\n');*/
    }
    return 0;
}