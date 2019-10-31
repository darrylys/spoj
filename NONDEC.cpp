#include<stdio.h>
#include<string.h>

#define MXN 1005
#define MOD 98765431
#define DEBUG
#define ll long long

int dp[MXN][10][10];
int sdp[MXN][10][10];
char S[4][MXN];
int rf[4][10][10];

void build() {
    // prep
    for (int d1=0; d1<=9; ++d1) {
        dp[1][d1][d1] = 1;
    }
    
    for (int n=2; n<MXN; ++n) {
        for (int d1=0; d1<=9; ++d1) {
            for (int d2=d1, p; d2<=9; ++d2) {
                dp[n][d1][d2] = dp[n-1][d1][d2];
                for (int dx=d1; dx<=d2; ++dx) {
                    dp[n][d1][d2] += (dp[n-1][dx][d2] - dp[n-2][dx][d2] + MOD );
                    if (dp[n][d1][d2] >= MOD) dp[n][d1][d2] %= MOD;
                }
            }
        }
    }
    
    // sum
    for (int n=1; n<MXN; ++n) {
        for (int d1=0; d1<=9; ++d1) {
            for (int d2=0; d2<=9; ++d2) {
                sdp[n][d1][d2] = ((d1 ? sdp[n][d1-1][d2] : 0) + dp[n][d1][d2]);
                if (sdp[n][d1][d2] >= MOD) sdp[n][d1][d2] %= MOD;
            }
        }
    }
}

void calc(int f[][10], char* bound, int len) {
    
    for (int d=0; d<=9; ++d) {
        for (int e=0; e<=9; ++e) {
            f[d][e] = dp[len-1][d][e];
        }
    }
    
    for (int d=1; d<bound[0]-'0'; ++d) {
        for (int e=d; e<=9; ++e) {
            f[d][e] += (dp[len][d][e] - dp[len-1][d][e] + MOD);
            if (f[d][e] >= MOD) f[d][e] %= MOD;
        }
    }
    
    char fchar = bound[0]-'0';
    char prevchar = fchar, currchar;
    for (int p=1; p<len; ++p) {
        currchar = bound[p]-'0';
        if (currchar >= prevchar) {
            for (int e=prevchar, ta, tb; e<=9; ++e) {
                ta = sdp[len-p][currchar-1][e] - sdp[len-p][prevchar-1][e] + MOD;
                tb = sdp[len-p-1][currchar-1][e] - sdp[len-p-1][prevchar-1][e] + MOD;
                
                f[fchar][e] += (ta - tb + MOD);
                if (f[fchar][e] >= MOD) f[fchar][e] %= MOD;
                //f[fchar][e] %= MOD;
            }
        } else {
            break;
        }
        prevchar = currchar;
    }
}

int incr(char* b, int len) {
    int ca = 0;
    for (int i=len-1; i>=0; --i) {
        if (b[i] < '9') {
            b[i]++;
            ca = 0;
            break;
        } else {
            b[i] = '0';
            ca = 1;
        }
    }
    if (ca) {
        for (int i=len; i>=1; --i) {
            b[i] = b[i-1];
        }
        b[0] = ca+'0';
    }
    return len+ca;
}

void decr(int f[][10], int g[][10]) {
    for (int i=0; i<=9; ++i) {
        for (int j=0; j<=9; ++j) {
            f[i][j] = (f[i][j] - g[i][j] + MOD)%MOD;
        }
    }
}

int main() {
    build();
    
    int t, len[4], sum;
    scanf ("%d", &t);
    while (t--) {
        scanf("%s %s %s %s", S[0], S[1], S[2], S[3]);
        for (int i=0; i<4; ++i) {
            len[i] = strlen(S[i]);
        }
        
        len[1] = incr(S[1], len[1]);
        len[3] = incr(S[3], len[3]);
        
        for (int i=0; i<4; ++i) {
            calc(rf[i], S[i], len[i]);
        }
        
        /*
        for (int n=0; n<4; ++n) {
            printf("rf[%d]=\n*****************************************************************************\n", n);
            for (int i=0; i<=9; ++i) {
                for (int j=0; j<=9; ++j) {
                    printf("[%d,%d]=%d\t", i, j, rf[n][i][j]);
                }
                putchar('\n');
            }
        }*/
        
        for (int i=0; i<4; i+=2) {
            decr(rf[i+1], rf[i]);
        }
        // X = [1], Y = [3]
        sum = 0;
        for (int dx1=1; dx1<=9; ++dx1) {
            for (int dx2=dx1; dx2<=9; ++dx2) {
                for (int dy1=dx2; dy1<=9; ++dy1) {
                    for (int dy2=dy1; dy2<=9; ++dy2) {
                        sum = (sum + ((ll)rf[1][dx1][dx2] * rf[3][dy1][dy2])%MOD)%MOD;
                    }
                }
            }
        }
        printf("%d\n", sum);
    }
    return 0;
    
    /*{ //scope bound
        for (int n=1; n<10; ++n) {
            printf("dp\nn=%d\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n", n);
            for (int d1=0; d1<=9; ++d1) {
                for (int d2=0; d2<=9; ++d2) {
                    printf("[%d,%d]=%d\t", d1, d2, dp[n][d1][d2]);
                }
                putchar('\n');
            }
        }
        putchar('\n');
        for (int n=1; n<10; ++n) {
            printf("sdp\nn=%d\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n", n);
            for (int d1=0; d1<=9; ++d1) {
                for (int d2=0; d2<=9; ++d2) {
                    printf("[%d,%d]=%d\t", d1, d2, sdp[n][d1][d2]);
                }
                putchar('\n');
            }
        }
    }*/
}
